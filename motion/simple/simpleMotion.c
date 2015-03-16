#include "simpleMotion.h"
#include "../motion.h"

#include "../../common/math/cenMath.h"

#include "../parameters/motionParameterType.h"
#include "../parameters/motionParameter.h"

#include "../pid/detectedMotionType.h"
#include "../pid/pid.h"
#include "../pid/pidMotion.h"
#include "../pid/profile/pidMotionProfileComputer.h"

#include "../position/coders.h"
#include "../position/trajectory.h"

#include "../../device/motor/pwmMotor.h"

#include "../../robot/kinematics/robotKinematics.h"

// MAIN FUNCTIONS

/**
 * Stop the robot.
 */
void stopPosition(bool maintainPositionValue) {
    updateTrajectoryAndClearCoders();

    if (maintainPositionValue) {
        maintainPosition();
    } else {
        // Avoid that robot reachs his position, and stops the motors
        setMustReachPosition(false);
    }
    // Avoid that the robot considered he will remain the initial speed for next move (it is stopped).
    clearInitialSpeeds();

    stopMotors();
}

void maintainPosition(void) {
    gotoPosition(0.0f, 0.0f, 0.0f, 0.0f);
}

// -> Go/Back

float forwardSimple(float pulse) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD);
    gotoPosition(pulse, pulse, motionParameter->a, motionParameter->speed);
    return pulse;
}

float backwardSimple(float pulse) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD);
    gotoPosition(-pulse, pulse, motionParameter->a, motionParameter->speed);
    return -pulse;
}

// -> Rotation

float leftSimple(float pulse) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION);
    gotoPosition(-pulse, pulse, motionParameter->a, motionParameter->speed);
    return -pulse;
}

float rightSimple(float pulse) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION);
    gotoPosition(pulse, pulse, motionParameter->a, motionParameter->speed);
    return pulse;
}

// -> OneWheel

float leftOneWheelSimple(float pulse) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION_ONE_WHEEL);
    gotoPosition(0, pulse, motionParameter->a, motionParameter->speed);
    return pulse;
}

float rightOneWheelSimple(float pulse) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION_ONE_WHEEL);
    gotoPosition(pulse, 0, motionParameter->a, motionParameter->speed);
    return pulse;
}

// MM OR DEGREE FUNCTIONS

float forwardMM(float distanceInMM, float a, float speed) {
    RobotKinematics* robotKinematics = getRobotKinematics();
    float leftWheelLengthForOnePulse = getLeftWheelLengthForOnePulse(robotKinematics);
    float rightWheelLengthForOnePulse = getRightWheelLengthForOnePulse(robotKinematics);

    float realDistanceLeft = distanceInMM / leftWheelLengthForOnePulse;
    float realDistanceRight = distanceInMM / rightWheelLengthForOnePulse;

    // Go at a position in millimeter
    gotoPosition(realDistanceLeft, realDistanceRight, a, speed);

    return distanceInMM;
}

float backwardMM(float distanceInMM, float a, float speed) {
    // Go at a position in millimeter
    forwardMM(-distanceInMM, a, speed);
    return -distanceInMM;
}

float rotationDegree(float angleDeciDegree, float a, float speed) {
    float angleRadius = angleDeciDegree * PI_DIVIDE_1800;
    RobotKinematics* robotKinematics = getRobotKinematics();
    float leftWheelLengthForOnePulse = getLeftWheelLengthForOnePulse(robotKinematics);
    float rightWheelLengthForOnePulse = getRightWheelLengthForOnePulse(robotKinematics);
    float wheelsDistanceFromCenter = getWheelsDistanceFromCenter(robotKinematics);
    float realDistanceLeft = -(wheelsDistanceFromCenter * angleRadius) / leftWheelLengthForOnePulse;
    float realDistanceRight = (wheelsDistanceFromCenter * angleRadius) / rightWheelLengthForOnePulse;
    gotoPosition(realDistanceLeft, realDistanceRight, a, speed);

    return angleDeciDegree;
}

float rotationMilliDegree(float angleMilliDegree, float a, float speed) {
    rotationDegree(angleMilliDegree * 0.001f, a, speed);

    return angleMilliDegree;
}

// -> rotation left/right

float leftDegree(float angleDegree, float a, float speed) {
    return rotationDegree(angleDegree, a, speed);
}

float leftMilliDegree(float angleMilliDegree, float a, float speed) {
    return rotationMilliDegree(angleMilliDegree, a, speed);
}

float rightDegree(float angleDegree, float a, float speed) {
    return rotationDegree(-angleDegree, a, speed);
}

float rightMilliDegree(float angleMilliDegree, float a, float speed) {
    return rotationMilliDegree(-angleMilliDegree, a, speed);
}

// -> rotation one Wheel

void leftOneWheelDegree(float angleDegree, float a, float speed) {
    // We multiply by 2, because, only one wheel rotates
    float angleRadius = angleDegree * PI_DIVIDE_1800 * 2.0f;
    RobotKinematics* robotKinematics = getRobotKinematics();
    float leftWheelLengthForOnePulse = getLeftWheelLengthForOnePulse(robotKinematics);
    float wheelsDistanceFromCenter = getWheelsDistanceFromCenter(robotKinematics);

    float realDistanceRight = (wheelsDistanceFromCenter * angleRadius) / leftWheelLengthForOnePulse;
    gotoPosition(0.0f, realDistanceRight, a, speed);
}

void rightOneWheelDegree(float angleDegree, float a, float speed) {
    // We multiply by 2, because, only one wheel rotates
    float angleRadius = angleDegree * PI_DIVIDE_1800 * 2.0f;
    RobotKinematics* robotKinematics = getRobotKinematics();
    float rightWheelLengthForOnePulse = getRightWheelLengthForOnePulse(robotKinematics);
    float wheelsDistanceFromCenter = getWheelsDistanceFromCenter(robotKinematics);

    float realDistanceLeft = (wheelsDistanceFromCenter * angleRadius) / rightWheelLengthForOnePulse;
    gotoPosition(realDistanceLeft, 0.0f, a, speed);
}

// SIMPLEST FUNCTION

// -> Go / Back

float forwardSimpleMM(float distanceInMM) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD);
    return forwardMM(distanceInMM, motionParameter->a, motionParameter->speed);
}

float backwardSimpleMM(float distanceInMM) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD);
    return backwardMM(distanceInMM, motionParameter->a, motionParameter->speed);
}

// -> Left / Right

float leftSimpleDegree(float angleDegree) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION);
    return leftDegree(angleDegree, motionParameter->a, motionParameter->speed);
}

float leftSimpleMilliDegree(float angleMilliDegree) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION);
    return leftMilliDegree(angleMilliDegree, motionParameter->a, motionParameter->speed);
}

float rightSimpleDegree(float angleDegree) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION);
    return rightDegree(angleDegree, motionParameter->a, motionParameter->speed);
}

float rightSimpleMilliDegree(float angleMilliDegree) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION);
    return rightMilliDegree(angleMilliDegree, motionParameter->a, motionParameter->speed);
}

// -> Left / Right : One Wheel

void leftOneWheelSimpleDegree(float angleDegree) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION_ONE_WHEEL);
    leftOneWheelDegree(angleDegree, motionParameter->a, motionParameter->speed);
}

void rightOneWheelSimpleDegree(float angleDegree) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION_ONE_WHEEL);
    rightOneWheelDegree(angleDegree, motionParameter->a, motionParameter->speed);
}

// With Wait

float forwardSimpleMMAndWait(float distanceInMM) {
    forwardSimpleMM(distanceInMM);
    handleAndWaitFreeMotion();
    return distanceInMM;
}

float backwardSimpleMMAndWait(float distanceInMM) {
    backwardSimpleMM(distanceInMM);
    handleAndWaitFreeMotion();
    return distanceInMM;
}

float leftSimpleDegreeAndWait(float angleDegree) {
    leftSimpleDegree(angleDegree);
    handleAndWaitFreeMotion();
    return angleDegree;
}

float leftSimpleMilliDegreeAndWait(float angleMilliDegree) {
    leftSimpleMilliDegree(angleMilliDegree);
    handleAndWaitFreeMotion();
    return angleMilliDegree;
}

float rightSimpleDegreeAndWait(float angleDegree) {
    rightSimpleDegree(angleDegree);
    handleAndWaitFreeMotion();
    return -angleDegree;
}

float rightSimpleMilliDegreeAndWait(float angleMilliDegree) {
    rightSimpleMilliDegree(angleMilliDegree);
    handleAndWaitFreeMotion();
    return -angleMilliDegree;
}
