#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <stdbool.h>

#include "trajectory.h"
#include "trajectoryType.h"

#include "../../common/2d/2d.h"

#include "../../common/commons.h"
#include "../../common/math/cenMath.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

// TO REMOVE
#include "../../device/deviceConstants.h"

#include "../../motion/position/coders.h"
#include "../../motion/pid/pid.h"
#include "../../robot/kinematics/robotKinematics.h"

// Position update threshold in mm
// If No Threshold, we compute at the end of a trajectory
#define UPDATE_THRESHOLD 1.0f

// Position on the board in true length
static TrajectoryInfo trajectory = {
    {
        // trajectory->position->pos
        {
            // trajectory->position->pos.x
            0.0f,
            // trajectory->position->pos.y
            0.0f
        },
        // trajectory->position->orientation
        0.0f,
        // trajectory->position->initialOrientation
        0.0f,
    },
    // trajectory->lastLeft,
    0.0f,
    // trajectory->lastRight,
    0.0f,
    // trajectory->lastAngle
    0.0f
};

TrajectoryInfo* getTrajectory(void) {
    return &trajectory;
}

void initializeTrajectory(void) {
    clearTrajectory();
    trajectory.notifyChange = TRAJECTORY_THRESHOLD_NOTIFY_DEFAULT_VALUE;
    trajectory.thresholdDistance = TRAJECTORY_THRESHOLD_DISTANCE_MM_DEFAULT_VALUE;
    trajectory.thresholdAngleRadian = TRAJECTORY_THRESHOLD_ANGLE_RADIAN_DEFAULT_VALUE;
}

void clearLastNotificationData(void) {
    // Last notification value (egal to the position to avoid continuous "notification")
    trajectory.lastNotificationPosition.pos.x = trajectory.position.pos.x;
    trajectory.lastNotificationPosition.pos.y = trajectory.position.pos.y;
    trajectory.lastNotificationPosition.orientation = trajectory.position.orientation;
    // No meaning for initialOrientation for lastNotification
}

void clearTrajectory(void) {
    setPosition(0.0f, 0.0f, 0.0f);
    trajectory.lastLeft = 0.0f;
    trajectory.lastRight = 0.0f;
    trajectory.lastAngle = 0.0f;
    clearLastNotificationData();
}

void setPosition(float x, float y, float orientation) {
    trajectory.position.pos.x = x;
    trajectory.position.pos.y = y;
    trajectory.position.initialOrientation = orientation - trajectory.position.orientation + trajectory.position.initialOrientation;
    trajectory.position.orientation = orientation;
    trajectory.lastAngle = 0.0f;
}

bool adjustXPosition(float x, float thresholdDistance) {
    // We exclude the adjustment if we are too far (to avoid to introduce more error than we need)
    if (trajectory.position.pos.x < x - thresholdDistance || trajectory.position.pos.x > x + thresholdDistance) {
        return false;
    }
    trajectory.position.pos.x = x;
    trajectory.position.orientation = 0.0f;
    return true;
}

bool adjustYPosition(float y, float thresholdDistance) {
    // We exclude the adjustment if we are too far (to avoid to introduce more error than we need)
    if (trajectory.position.pos.x < y - thresholdDistance || trajectory.position.pos.y > y + thresholdDistance) {
        return false;
    }
    trajectory.position.pos.y = y;
    trajectory.position.orientation = 0.0f;
    return true;
}

bool adjustAngle(float thresholdAngle) {
    float quadranRadian = -PI;
    for (quadranRadian = -_2_PI; quadranRadian < _2_PI; quadranRadian += PI / 2) {
        if (trajectory.position.orientation > quadranRadian -thresholdAngle && trajectory.position.orientation < quadranRadian + thresholdAngle) {
            trajectory.position.orientation = quadranRadian;
            return true;
        }
    }
    return false;
}

Position* getPosition(void) {
    return &trajectory.position;
}

void debugTrajectoryVariables(char* valueName1, float value1, char* valueName2, float value2) {
    OutputStream* outputStream = getDebugOutputStreamLogger();
    appendStringAndDecf(outputStream, valueName1, value1);
    appendStringAndDecf(outputStream, valueName2, value2);
    appendCRLF(outputStream);
}

/**
 * @private
 * Computes and updates the position from the specified
 * values from the coders.
 * @param left the value of the left coder
 * @param right the value of the right coder
 * @return 1 if the position has been updated, 0 otherwise
 */
bool absoluteUpdateFromCoders(signed long left, signed long right, bool useThreshold, bool debug) {
    if (debug) {
        debugTrajectoryVariables("left=", (float) left, ", right=", (float) right);
    }
    RobotKinematics* robotKinematics = getRobotKinematics();
    float leftWheelLengthForOnePulse = getCoderLeftWheelLengthForOnePulse(robotKinematics);
    float rightWheelLengthForOnePulse = getCoderRightWheelLengthForOnePulse(robotKinematics);

    float l = (float) left * leftWheelLengthForOnePulse;
    float r = (float) right * rightWheelLengthForOnePulse;
    if (debug) {
        debugTrajectoryVariables("l=", l, ", r=", r);
    }
    float dl = l - trajectory.lastLeft;
    float dr = r - trajectory.lastRight;
    if (debug) {
        debugTrajectoryVariables("dl=", dl, ", dr=", dr);
    }
    if (useThreshold) {
        if (fabsf(dl) <= UPDATE_THRESHOLD && fabsf(dr) <= UPDATE_THRESHOLD) {
            return false;
        }
    }

    // difference des distances parcourues par les roues en m
    float dw = r - l;
    // orientation finale = difference des distances / demi-distance des roues
    float wheelsDistance = robotKinematics->coderWheelDistanceBetweenWheelsMM;
    float orientation = fmodf(dw / wheelsDistance, 2.0f * PI) + trajectory.lastAngle + trajectory.position.initialOrientation;
    // angle relatif au dernier mouvement
    // lastAngle is only used when we clear Coders !
    float relativePositionOrientation = trajectory.position.orientation;
    float angle = orientation - relativePositionOrientation;
    float meanOrientation = (orientation + relativePositionOrientation) / 2.0f;

    if (debug) {
        debugTrajectoryVariables("dw=", dw, ", orientation=", orientation);
        debugTrajectoryVariables("angle=", angle, ",meanOrientation=", meanOrientation);
    }

    // distance during last move
    float d = (dl + dr) / 2.0f;
    // project distance according the angle
    float k = 1.0f;
    if (angle != 0.0f) {
        float t = angle / 2.0f;
        k = sinf(t) / t;
    }

    float dx = d * k * cosf(meanOrientation);
    float dy = d * k * sinf(meanOrientation);
    if (debug) {
        debugTrajectoryVariables("dx=", dx, ", dy=", dy);
    }

    // update position
    trajectory.position.pos.x += dx;
    trajectory.position.pos.y += dy;
    trajectory.position.orientation = orientation;

    trajectory.lastLeft = l;
    trajectory.lastRight = r;

    return true;
}

void updateTrajectory() {
    signed long left = getCoderValue(CODER_LEFT);
    signed long right = getCoderValue(CODER_RIGHT);
    //    curveUpdateFromCoders(left, right);
    absoluteUpdateFromCoders(left, right, true, false);
}

void updateTrajectoryWithNoThreshold() {
    signed long left = getCoderValue(CODER_LEFT);
    signed long right = getCoderValue(CODER_RIGHT);
    // do not use threshold
    absoluteUpdateFromCoders(left, right, false, false);
}

void updateTrajectoryAndClearCoders() {
    updateTrajectoryWithNoThreshold();
    trajectory.lastAngle = trajectory.position.orientation - trajectory.position.initialOrientation;
    clearCoders();
    trajectory.lastLeft = 0;
    trajectory.lastRight = 0;
}

// NOTIFICATION

enum TrajectoryType computeTrajectoryType(float distanceSinceLastNotification, float angleRadianSinceLastNotification) {
    if (distanceSinceLastNotification < trajectory.thresholdDistance) {
        if (angleRadianSinceLastNotification < trajectory.thresholdAngleRadian) {
            return TRAJECTORY_TYPE_NONE;
        }
        // More near from a rotation even if the robot has moved
        return TRAJECTORY_TYPE_ROTATION;
    }
    else {
        Point* previousPoint = &(trajectory.lastNotificationPosition.pos);
        Point* currentPoint = &(trajectory.position.pos);

        float angleOfVectorRadian = angleOfVector(previousPoint, currentPoint);
        
        float orientation = trajectory.position.orientation;
        float orientationMod2PI = mod2PI(orientation - angleOfVectorRadian);
        // We are "more" in a back trajectoty type if we are in this quadran
        if (fabsf(orientationMod2PI) > PI / 2) {
            return TRAJECTORY_TYPE_BACKWARD;
        }
        return TRAJECTORY_TYPE_FORWARD;
    }
}

float getDistanceBetweenLastNotificationAndCurrentRobotPosition(void) {
    Point* lastNotificationPoint = &(trajectory.lastNotificationPosition.pos);
    Point* currentPosition = &(trajectory.position.pos);
    
    return distanceBetweenPoints(lastNotificationPoint, currentPosition);
}

float getAbsoluteAngleRadianBetweenLastNotificationAndCurrentRobotPosition(void) {
    float lastAngle = trajectory.position.orientation;
    float lastNotificationAngle = trajectory.lastNotificationPosition.orientation;
    
    return fabsf(lastAngle - lastNotificationAngle);
}
