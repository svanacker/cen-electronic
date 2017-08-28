#include "simpleMotion.h"
#include "../motion.h"

#include "../../common/math/cenMath.h"

#include "../parameters/motionParameterType.h"
#include "../parameters/motionParameter.h"

#include "../pid/alphaTheta.h"
#include "../pid/detectedMotionType.h"
#include "../pid/pid.h"
#include "../pid/pidMotion.h"
#include "../pid/profile/pidMotionProfileComputer.h"

#include "../position/coders.h"
#include "../position/trajectory.h"

#include "../../device/motor/pwmMotor.h"

#include "../../robot/kinematics/robotKinematics.h"

/**
* Go to a position
*/
void gotoPosition(PidMotion* pidMotion, float left, float right, float a, float speed) {

	// Update trajectory before clearing coders
	updateTrajectory();

	updateTrajectoryAndClearCoders();

	// resets the time
	clearPidTime();

	// determine the type of motion
	enum MotionParameterType motionParameterType = getMotionParameterType(left, right);
	// determine the pidType to execute motionParameterType
	enum PidType pidType = getPidType(motionParameterType);

	// Alpha / Theta
	float thetaNextPosition = computeTheta(left, right);
	float alphaNextPosition = computeAlpha(left, right);

	PidMotionDefinition* motionDefinition = pidMotionGetNextToWritePidMotionDefinition(pidMotion);
	motionDefinition->motionType = MOTION_TYPE_NORMAL;

	setNextPosition(pidMotion, motionDefinition, THETA, motionParameterType, pidType, thetaNextPosition, (float)a, (float)speed);
	setNextPosition(pidMotion, motionDefinition, ALPHA, motionParameterType, pidType, alphaNextPosition, (float)a, (float)speed);

	// OutputStream* outputStream = getDebugOutputStreamLogger();
	// printMotionInstruction(outputStream, &(pidMotionDefinition->inst[THETA]));
	// printMotionInstruction(outputStream, &(pidMotionDefinition->inst[ALPHA]));

	// Indicates that the robot must reach the position
	setMustReachPosition(pidMotion, true);
}


/**
 * Stop the robot.
 */
void stopPosition(PidMotion* pidMotion, bool maintainPositionValue) {
    updateTrajectoryAndClearCoders();

    if (maintainPositionValue) {
        maintainPosition(pidMotion);
    } else {
        // Avoid that robot reachs his position, and stops the motors
        setMustReachPosition(pidMotion, false);
    }
    // Avoid that the robot considered he will remain the initial speed for next move (it is stopped).
    clearInitialSpeeds(pidMotion);

    stopMotors();
}

void maintainPosition(PidMotion* pidMotion) {
    gotoPosition(pidMotion, 0.0f, 0.0f, 0.0f, 0.0f);
}


// -> Go/Back

float forwardSimple(PidMotion* pidMotion, float pulse) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD);
    gotoPosition(pidMotion, pulse, pulse, motionParameter->a, motionParameter->speed);
    return pulse;
}

float backwardSimple(PidMotion* pidMotion, float pulse) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD);
    gotoPosition(pidMotion, -pulse, -pulse, motionParameter->a, motionParameter->speed);
    return -pulse;
}

// -> Rotation

float leftSimple(PidMotion* pidMotion, float pulse) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION);
    gotoPosition(pidMotion, -pulse, pulse, motionParameter->a, motionParameter->speed);
    return -pulse;
}

float rightSimple(PidMotion* pidMotion, float pulse) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION);
    gotoPosition(pidMotion, pulse, pulse, motionParameter->a, motionParameter->speed);
    return pulse;
}

// -> OneWheel

float leftOneWheelSimple(PidMotion* pidMotion, float pulse) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION_ONE_WHEEL);
    gotoPosition(pidMotion, 0, pulse, motionParameter->a, motionParameter->speed);
    return pulse;
}

float rightOneWheelSimple(PidMotion* pidMotion, float pulse) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION_ONE_WHEEL);
    gotoPosition(pidMotion, pulse, 0, motionParameter->a, motionParameter->speed);
    return pulse;
}

// MM OR DEGREE FUNCTIONS

float forwardMM(PidMotion* pidMotion, float distanceInMM, float a, float speed) {
    RobotKinematics* robotKinematics = getRobotKinematics();
    float leftWheelLengthForOnePulse = getLeftWheelLengthForOnePulse(robotKinematics);
    float rightWheelLengthForOnePulse = getRightWheelLengthForOnePulse(robotKinematics);

    float realDistanceLeft = distanceInMM / leftWheelLengthForOnePulse;
    float realDistanceRight = distanceInMM / rightWheelLengthForOnePulse;

    // Go at a position in millimeter
    gotoPosition(pidMotion, realDistanceLeft, realDistanceRight, a, speed);

    return distanceInMM;
}

float backwardMM(PidMotion* pidMotion, float distanceInMM, float a, float speed) {
    // Go at a position in millimeter
    forwardMM(pidMotion, -distanceInMM, a, speed);
    return -distanceInMM;
}

float rotationDegree(PidMotion* pidMotion, float angleDeciDegree, float a, float speed) {
    float angleRadius = angleDeciDegree * PI_DIVIDE_1800;
    RobotKinematics* robotKinematics = getRobotKinematics();
    float leftWheelLengthForOnePulse = getLeftWheelLengthForOnePulse(robotKinematics);
    float rightWheelLengthForOnePulse = getRightWheelLengthForOnePulse(robotKinematics);
    float wheelsDistanceFromCenter = getWheelsDistanceFromCenter(robotKinematics);
    float realDistanceLeft = -(wheelsDistanceFromCenter * angleRadius) / leftWheelLengthForOnePulse;
    float realDistanceRight = (wheelsDistanceFromCenter * angleRadius) / rightWheelLengthForOnePulse;
    gotoPosition(pidMotion, realDistanceLeft, realDistanceRight, a, speed);

    return angleDeciDegree;
}

float rotationMilliDegree(PidMotion* pidMotion, float angleMilliDegree, float a, float speed) {
    rotationDegree(pidMotion, angleMilliDegree * 0.001f, a, speed);

    return angleMilliDegree;
}

// -> rotation left/right

float leftDegree(PidMotion* pidMotion, float angleDegree, float a, float speed) {
    return rotationDegree(pidMotion, angleDegree, a, speed);
}

float leftMilliDegree(PidMotion* pidMotion, float angleMilliDegree, float a, float speed) {
    return rotationMilliDegree(pidMotion, angleMilliDegree, a, speed);
}

float rightDegree(PidMotion* pidMotion, float angleDegree, float a, float speed) {
    return rotationDegree(pidMotion, -angleDegree, a, speed);
}

float rightMilliDegree(PidMotion* pidMotion, float angleMilliDegree, float a, float speed) {
    return rotationMilliDegree(pidMotion, -angleMilliDegree, a, speed);
}

// -> rotation one Wheel

void leftOneWheelDegree(PidMotion* pidMotion, float angleDegree, float a, float speed) {
    // We multiply by 2, because, only one wheel rotates
    float angleRadius = angleDegree * PI_DIVIDE_1800 * 2.0f;
    RobotKinematics* robotKinematics = getRobotKinematics();
    float leftWheelLengthForOnePulse = getLeftWheelLengthForOnePulse(robotKinematics);
    float wheelsDistanceFromCenter = getWheelsDistanceFromCenter(robotKinematics);

    float realDistanceRight = (wheelsDistanceFromCenter * angleRadius) / leftWheelLengthForOnePulse;
    gotoPosition(pidMotion, 0.0f, realDistanceRight, a, speed);
}

void rightOneWheelDegree(PidMotion* pidMotion, float angleDegree, float a, float speed) {
    // We multiply by 2, because, only one wheel rotates
    float angleRadius = angleDegree * PI_DIVIDE_1800 * 2.0f;
    RobotKinematics* robotKinematics = getRobotKinematics();
    float rightWheelLengthForOnePulse = getRightWheelLengthForOnePulse(robotKinematics);
    float wheelsDistanceFromCenter = getWheelsDistanceFromCenter(robotKinematics);

    float realDistanceLeft = (wheelsDistanceFromCenter * angleRadius) / rightWheelLengthForOnePulse;
    gotoPosition(pidMotion, realDistanceLeft, 0.0f, a, speed);
}

// SIMPLEST FUNCTION

// -> Go / Back

float forwardSimpleMM(PidMotion* pidMotion, float distanceInMM) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD);
    return forwardMM(pidMotion, distanceInMM, motionParameter->a, motionParameter->speed);
}

float backwardSimpleMM(PidMotion* pidMotion, float distanceInMM) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD);
    return backwardMM(pidMotion, distanceInMM, motionParameter->a, motionParameter->speed);
}

// -> Left / Right

float leftSimpleDegree(PidMotion* pidMotion, float angleDegree) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION);
    return leftDegree(pidMotion, angleDegree, motionParameter->a, motionParameter->speed);
}

float leftSimpleMilliDegree(PidMotion* pidMotion, float angleMilliDegree) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION);
    return leftMilliDegree(pidMotion, angleMilliDegree, motionParameter->a, motionParameter->speed);
}

float rightSimpleDegree(PidMotion* pidMotion, float angleDegree) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION);
    return rightDegree(pidMotion, angleDegree, motionParameter->a, motionParameter->speed);
}

float rightSimpleMilliDegree(PidMotion* pidMotion, float angleMilliDegree) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION);
    return rightMilliDegree(pidMotion, angleMilliDegree, motionParameter->a, motionParameter->speed);
}

// -> Left / Right : One Wheel

void leftOneWheelSimpleDegree(PidMotion* pidMotion, float angleDegree) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION_ONE_WHEEL);
    leftOneWheelDegree(pidMotion, angleDegree, motionParameter->a, motionParameter->speed);
}

void rightOneWheelSimpleDegree(PidMotion* pidMotion, float angleDegree) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION_ONE_WHEEL);
    rightOneWheelDegree(pidMotion, angleDegree, motionParameter->a, motionParameter->speed);
}

// With Wait

float forwardSimpleMMAndWait(PidMotion* pidMotion, float distanceInMM) {
    forwardSimpleMM(pidMotion, distanceInMM);
    handleAndWaitFreeMotion(pidMotion);
    return distanceInMM;
}

float backwardSimpleMMAndWait(PidMotion* pidMotion, float distanceInMM) {
    backwardSimpleMM(pidMotion, distanceInMM);
    handleAndWaitFreeMotion(pidMotion);
    return distanceInMM;
}

float leftSimpleDegreeAndWait(PidMotion* pidMotion, float angleDegree) {
    leftSimpleDegree(pidMotion, angleDegree);
    handleAndWaitFreeMotion(pidMotion);
    return angleDegree;
}

float leftSimpleMilliDegreeAndWait(PidMotion* pidMotion, float angleMilliDegree) {
    leftSimpleMilliDegree(pidMotion, angleMilliDegree);
    handleAndWaitFreeMotion(pidMotion);
    return angleMilliDegree;
}

float rightSimpleDegreeAndWait(PidMotion* pidMotion, float angleDegree) {
    rightSimpleDegree(pidMotion, angleDegree);
    handleAndWaitFreeMotion(pidMotion);
    return -angleDegree;
}

float rightSimpleMilliDegreeAndWait(PidMotion* pidMotion, float angleMilliDegree) {
    rightSimpleMilliDegree(pidMotion, angleMilliDegree);
    handleAndWaitFreeMotion(pidMotion);
    return -angleMilliDegree;
}
