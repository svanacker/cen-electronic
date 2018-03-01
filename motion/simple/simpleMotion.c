#include "simpleMotion.h"
#include "../motion.h"

#include "../../common/io/OutputStream.h"
#include "../../common/log/logger.h"
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
void gotoSimplePosition(PidMotion* pidMotion, float left, float right, float a, float speed, OutputStream* notificationOutputStream) {
	// determine the type of motion
	enum MotionParameterType motionParameterType = getMotionParameterType(left, right);
	// determine the pidType to execute motionParameterType
	enum PidType pidType = getPidType(motionParameterType);

	// Alpha / Theta
	float thetaNextPosition = computeTheta(left, right);
	float alphaNextPosition = computeAlpha(left, right);

	PidMotionDefinition* motionDefinition = pidMotionGetNextToWritePidMotionDefinition(pidMotion);
	motionDefinition->motionType = MOTION_TYPE_NORMAL;
	motionDefinition->notificationOutputStream = notificationOutputStream;

	setNextPosition(motionDefinition, THETA, motionParameterType, pidType, thetaNextPosition, (float)a, (float)speed);
	setNextPosition(motionDefinition, ALPHA, motionParameterType, pidType, alphaNextPosition, (float)a, (float)speed);

	/*
	OutputStream* outputStream = getDebugOutputStreamLogger();
	printMotionInstruction(outputStream, &(motionDefinition->inst[THETA]));
	printMotionInstruction(outputStream, &(motionDefinition->inst[ALPHA]));
	*/
    // All main information are defined
    motionDefinition->state = PID_MOTION_DEFINITION_STATE_SET;
}


/**
 * Stop the robot.
 */
void stopPosition(PidMotion* pidMotion, bool maintainPositionValue, OutputStream* notificationOutputStream) {
    updateTrajectoryAndClearCoders();

    if (maintainPositionValue) {
        maintainPosition(pidMotion, notificationOutputStream);
    }
    
    // Avoid that the robot considered he will remain the initial speed for next move (it is stopped).
    clearInitialSpeeds(pidMotion);

    stopMotors();
}

void maintainPosition(PidMotion* pidMotion, OutputStream* notificationOutputStream) {
    gotoSimplePosition(pidMotion, 0.0f, 0.0f, 0.0f, 0.0f, notificationOutputStream);
}


// -> Go/Back

float forwardSimple(PidMotion* pidMotion, float pulse, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD);
    gotoSimplePosition(pidMotion, pulse, pulse, motionParameter->a, motionParameter->speed, notificationOutputStream);
    return pulse;
}

float backwardSimple(PidMotion* pidMotion, float pulse, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD);
    gotoSimplePosition(pidMotion, -pulse, -pulse, motionParameter->a, motionParameter->speed, notificationOutputStream);
    return -pulse;
}

// -> Rotation

float leftSimple(PidMotion* pidMotion, float pulse, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION);
    gotoSimplePosition(pidMotion, -pulse, pulse, motionParameter->a, motionParameter->speed, notificationOutputStream);
    return -pulse;
}

float rightSimple(PidMotion* pidMotion, float pulse, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION);
    gotoSimplePosition(pidMotion, pulse, pulse, motionParameter->a, motionParameter->speed, notificationOutputStream);
    return pulse;
}

// -> OneWheel

float leftOneWheelSimple(PidMotion* pidMotion, float pulse, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION_ONE_WHEEL);
    gotoSimplePosition(pidMotion, 0, pulse, motionParameter->a, motionParameter->speed, notificationOutputStream);
    return pulse;
}

float rightOneWheelSimple(PidMotion* pidMotion, float pulse, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION_ONE_WHEEL);
    gotoSimplePosition(pidMotion, pulse, 0, motionParameter->a, motionParameter->speed, notificationOutputStream);
    return pulse;
}

// MM OR DEGREE FUNCTIONS

float forwardMM(PidMotion* pidMotion, float distanceInMM, float a, float speed, OutputStream* notificationOutputStream) {
    RobotKinematics* robotKinematics = getRobotKinematics();
    float leftWheelLengthForOnePulse = getLeftWheelLengthForOnePulse(robotKinematics);
    float rightWheelLengthForOnePulse = getRightWheelLengthForOnePulse(robotKinematics);

    float realDistanceLeft = distanceInMM / leftWheelLengthForOnePulse;
    float realDistanceRight = distanceInMM / rightWheelLengthForOnePulse;

    // Go at a position in millimeter
    gotoSimplePosition(pidMotion, realDistanceLeft, realDistanceRight, a, speed, notificationOutputStream);

    return distanceInMM;
}

float backwardMM(PidMotion* pidMotion, float distanceInMM, float a, float speed, OutputStream* notificationOutputStream) {
    // Go at a position in millimeter
    forwardMM(pidMotion, -distanceInMM, a, speed, notificationOutputStream);
    return -distanceInMM;
}

float rotationDegree(PidMotion* pidMotion, float angleDeciDegree, float a, float speed, OutputStream* notificationOutputStream) {
    float angleRadius = angleDeciDegree * PI_DIVIDE_1800;
    RobotKinematics* robotKinematics = getRobotKinematics();
    float leftWheelLengthForOnePulse = getLeftWheelLengthForOnePulse(robotKinematics);
    float rightWheelLengthForOnePulse = getRightWheelLengthForOnePulse(robotKinematics);
    float wheelsDistanceFromCenter = getWheelsDistanceFromCenter(robotKinematics);
    float realDistanceLeft = -(wheelsDistanceFromCenter * angleRadius) / leftWheelLengthForOnePulse;
    float realDistanceRight = (wheelsDistanceFromCenter * angleRadius) / rightWheelLengthForOnePulse;
    gotoSimplePosition(pidMotion, realDistanceLeft, realDistanceRight, a, speed, notificationOutputStream);

    return angleDeciDegree;
}

float rotationMilliDegree(PidMotion* pidMotion, float angleMilliDegree, float a, float speed, OutputStream* notificationOutputStream) {
    rotationDegree(pidMotion, angleMilliDegree * 0.001f, a, speed, notificationOutputStream);

    return angleMilliDegree;
}

// -> rotation left/right

float leftDegree(PidMotion* pidMotion, float angleDegree, float a, float speed, OutputStream* notificationOutputStream) {
    return rotationDegree(pidMotion, angleDegree, a, speed, notificationOutputStream);
}

float leftMilliDegree(PidMotion* pidMotion, float angleMilliDegree, float a, float speed, OutputStream* notificationOutputStream) {
    return rotationMilliDegree(pidMotion, angleMilliDegree, a, speed, notificationOutputStream);
}

float rightDegree(PidMotion* pidMotion, float angleDegree, float a, float speed, OutputStream* notificationOutputStream) {
    return rotationDegree(pidMotion, -angleDegree, a, speed, notificationOutputStream);
}

float rightMilliDegree(PidMotion* pidMotion, float angleMilliDegree, float a, float speed, OutputStream* notificationOutputStream) {
    return rotationMilliDegree(pidMotion, -angleMilliDegree, a, speed, notificationOutputStream);
}

// -> rotation one Wheel

void leftOneWheelDegree(PidMotion* pidMotion, float angleDegree, float a, float speed, OutputStream* notificationOutputStream) {
    // We multiply by 2, because, only one wheel rotates
    float angleRadius = angleDegree * PI_DIVIDE_1800 * 2.0f;
    RobotKinematics* robotKinematics = getRobotKinematics();
    float leftWheelLengthForOnePulse = getLeftWheelLengthForOnePulse(robotKinematics);
    float wheelsDistanceFromCenter = getWheelsDistanceFromCenter(robotKinematics);

    float realDistanceRight = (wheelsDistanceFromCenter * angleRadius) / leftWheelLengthForOnePulse;
    gotoSimplePosition(pidMotion, 0.0f, realDistanceRight, a, speed, notificationOutputStream);
}

void rightOneWheelDegree(PidMotion* pidMotion, float angleDegree, float a, float speed, OutputStream* notificationOutputStream) {
    // We multiply by 2, because, only one wheel rotates
    float angleRadius = angleDegree * PI_DIVIDE_1800 * 2.0f;
    RobotKinematics* robotKinematics = getRobotKinematics();
    float rightWheelLengthForOnePulse = getRightWheelLengthForOnePulse(robotKinematics);
    float wheelsDistanceFromCenter = getWheelsDistanceFromCenter(robotKinematics);

    float realDistanceLeft = (wheelsDistanceFromCenter * angleRadius) / rightWheelLengthForOnePulse;
    gotoSimplePosition(pidMotion, realDistanceLeft, 0.0f, a, speed, notificationOutputStream);
}

// SIMPLEST FUNCTION

// -> Go / Back

float forwardSimpleMM(PidMotion* pidMotion, float distanceInMM, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD);
    return forwardMM(pidMotion, distanceInMM, motionParameter->a, motionParameter->speed, notificationOutputStream);
}

float backwardSimpleMM(PidMotion* pidMotion, float distanceInMM, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD);
    return backwardMM(pidMotion, distanceInMM, motionParameter->a, motionParameter->speed, notificationOutputStream);
}

// -> Left / Right

float leftSimpleDegree(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION);
    return leftDegree(pidMotion, angleDegree, motionParameter->a, motionParameter->speed, notificationOutputStream);
}

float leftSimpleMilliDegree(PidMotion* pidMotion, float angleMilliDegree, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION);
    return leftMilliDegree(pidMotion, angleMilliDegree, motionParameter->a, motionParameter->speed, notificationOutputStream);
}

float rightSimpleDegree(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION);
    return rightDegree(pidMotion, angleDegree, motionParameter->a, motionParameter->speed, notificationOutputStream);
}

float rightSimpleMilliDegree(PidMotion* pidMotion, float angleMilliDegree, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION);
    return rightMilliDegree(pidMotion, angleMilliDegree, motionParameter->a, motionParameter->speed, notificationOutputStream);
}

// -> Left / Right : One Wheel

void leftOneWheelSimpleDegree(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION_ONE_WHEEL);
    leftOneWheelDegree(pidMotion, angleDegree, motionParameter->a, motionParameter->speed, notificationOutputStream);
}

void rightOneWheelSimpleDegree(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_ROTATION_ONE_WHEEL);
    rightOneWheelDegree(pidMotion, angleDegree, motionParameter->a, motionParameter->speed, notificationOutputStream);
}

// With Wait

float forwardSimpleMMAndWait(PidMotion* pidMotion, float distanceInMM, OutputStream* notificationOutputStream) {
    forwardSimpleMM(pidMotion, distanceInMM, notificationOutputStream);
    handleAndWaitFreeMotion(pidMotion);
    return distanceInMM;
}

float backwardSimpleMMAndWait(PidMotion* pidMotion, float distanceInMM, OutputStream* notificationOutputStream) {
    backwardSimpleMM(pidMotion, distanceInMM, notificationOutputStream);
    handleAndWaitFreeMotion(pidMotion);
    return distanceInMM;
}

float leftSimpleDegreeAndWait(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream) {
    leftSimpleDegree(pidMotion, angleDegree, notificationOutputStream);
    handleAndWaitFreeMotion(pidMotion);
    return angleDegree;
}

float leftSimpleMilliDegreeAndWait(PidMotion* pidMotion, float angleMilliDegree, OutputStream* notificationOutputStream) {
    leftSimpleMilliDegree(pidMotion, angleMilliDegree, notificationOutputStream);
    handleAndWaitFreeMotion(pidMotion);
    return angleMilliDegree;
}

float rightSimpleDegreeAndWait(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream) {
    rightSimpleDegree(pidMotion, angleDegree, notificationOutputStream);
    handleAndWaitFreeMotion(pidMotion);
    return -angleDegree;
}

float rightSimpleMilliDegreeAndWait(PidMotion* pidMotion, float angleMilliDegree, OutputStream* notificationOutputStream) {
    rightSimpleMilliDegree(pidMotion, angleMilliDegree, notificationOutputStream);
    handleAndWaitFreeMotion(pidMotion);
    return -angleMilliDegree;
}
