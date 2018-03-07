#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <stdbool.h>

#include "trajectory.h"

#include "../../common/2d/2d.h"

#include "../../common/commons.h"
#include "../../common/math/cenMath.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

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
}


void clearTrajectory(void) {
    setPosition(0.0f, 0.0f, 0.0f);
    trajectory.lastLeft = 0.0f;
    trajectory.lastRight = 0.0f;
    trajectory.lastAngle = 0.0f;
}

void setPosition(float x, float y, float orientation) {
    trajectory.position.pos.x = x;
    trajectory.position.pos.y = y;
    trajectory.position.initialOrientation = orientation - trajectory.position.orientation + trajectory.position.initialOrientation;
    trajectory.position.orientation = orientation;
    trajectory.lastAngle = 0.0f;
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
        debugTrajectoryVariables("dw=", dw, ", orientationi=", orientation);
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

