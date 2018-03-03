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
void gotoSimplePosition(PidMotion* pidMotion, float leftPulse, float rightPulse, float a, float speed, OutputStream* notificationOutputStream) {
	// determine the type of motion
	enum MotionParameterType motionParameterType = getMotionParameterType(leftPulse, rightPulse);
	// determine the pidType to execute motionParameterType
	enum PidType pidType = getPidType(motionParameterType);

	// Alpha / Theta
	float thetaNextPosition = computeTheta(leftPulse, rightPulse);
	float alphaNextPosition = computeAlpha(leftPulse, rightPulse);

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
    MotionParameter* motionParameter = getMotionParameters(MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD);
    gotoSimplePosition(pidMotion, pulse, pulse, motionParameter->a, motionParameter->speed, notificationOutputStream);
    return pulse;
}

float backwardSimple(PidMotion* pidMotion, float pulse, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getMotionParameters(MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD);
    gotoSimplePosition(pidMotion, -pulse, -pulse, motionParameter->a, motionParameter->speed, notificationOutputStream);
    return -pulse;
}

// -> Rotation

float leftSimple(PidMotion* pidMotion, float pulse, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getMotionParameters(MOTION_PARAMETER_TYPE_ROTATION);
    gotoSimplePosition(pidMotion, -pulse, pulse, motionParameter->a, motionParameter->speed, notificationOutputStream);
    return -pulse;
}

float rightSimple(PidMotion* pidMotion, float pulse, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getMotionParameters(MOTION_PARAMETER_TYPE_ROTATION);
    gotoSimplePosition(pidMotion, pulse, pulse, motionParameter->a, motionParameter->speed, notificationOutputStream);
    return pulse;
}

// -> OneWheel

float leftOneWheelSimple(PidMotion* pidMotion, float pulse, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getMotionParameters(MOTION_PARAMETER_TYPE_ROTATION_ONE_WHEEL);
    gotoSimplePosition(pidMotion, 0, pulse, motionParameter->a, motionParameter->speed, notificationOutputStream);
    return pulse;
}

float rightOneWheelSimple(PidMotion* pidMotion, float pulse, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getMotionParameters(MOTION_PARAMETER_TYPE_ROTATION_ONE_WHEEL);
    gotoSimplePosition(pidMotion, pulse, 0, motionParameter->a, motionParameter->speed, notificationOutputStream);
    return pulse;
}

// MM OR DEGREE FUNCTIONS

float forwardMM(PidMotion* pidMotion, float distanceInMM, float a, float speed, OutputStream* notificationOutputStream) {
    RobotKinematics* robotKinematics = getRobotKinematics();
    float leftWheelLengthForOnePulse = getLeftWheelLengthForOnePulse(robotKinematics);
    float rightWheelLengthForOnePulse = getRightWheelLengthForOnePulse(robotKinematics);

    float leftPulse = distanceInMM / leftWheelLengthForOnePulse;
    float rightPulse = distanceInMM / rightWheelLengthForOnePulse;

    // Go at a position in millimeter
    gotoSimplePosition(pidMotion, leftPulse, rightPulse, a, speed, notificationOutputStream);

    return distanceInMM;
}

float backwardMM(PidMotion* pidMotion, float distanceInMM, float a, float speed, OutputStream* notificationOutputStream) {
    // Go at a position in millimeter
    forwardMM(pidMotion, -distanceInMM, a, speed, notificationOutputStream);
    return -distanceInMM;
}

float rotationDeciDegree(PidMotion* pidMotion, float angleDeciDegree, float a, float speed, OutputStream* notificationOutputStream) {
    RobotKinematics* robotKinematics = getRobotKinematics();
    float leftPulse = rotationInDeciDegreeToRealDistanceForLeftWheel(robotKinematics, angleDeciDegree);
    float rightPulse = rotationInDeciDegreeToRealDistanceForRightWheel(robotKinematics, angleDeciDegree);

    gotoSimplePosition(pidMotion, leftPulse, rightPulse, a, speed, notificationOutputStream);

    return angleDeciDegree;
}

// -> rotation left/right

float leftDeciDegree(PidMotion* pidMotion, float angleDeciDegree, float a, float speed, OutputStream* notificationOutputStream) {
    return rotationDeciDegree(pidMotion, angleDeciDegree, a, speed, notificationOutputStream);
}

float rightDeciDegree(PidMotion* pidMotion, float angleDeciDegree, float a, float speed, OutputStream* notificationOutputStream) {
    return rotationDeciDegree(pidMotion, -angleDeciDegree, a, speed, notificationOutputStream);
}

// -> rotation one Wheel

void leftOneWheelDeciDegree(PidMotion* pidMotion, float angleDeciDegree, float a, float speed, OutputStream* notificationOutputStream) {
    // We multiply by 2, because, only one wheel rotates
    float angleRadius = angleDeciDegree * PI_DIVIDE_1800 * 2.0f;
    RobotKinematics* robotKinematics = getRobotKinematics();
    float leftWheelLengthForOnePulse = getLeftWheelLengthForOnePulse(robotKinematics);
    float wheelsDistanceFromCenter = getWheelsDistanceFromCenter(robotKinematics);

    float realDistanceRight = (wheelsDistanceFromCenter * angleRadius) / leftWheelLengthForOnePulse;
    gotoSimplePosition(pidMotion, 0.0f, realDistanceRight, a, speed, notificationOutputStream);
}

void rightOneWheelDeciDegree(PidMotion* pidMotion, float angleDeciDegree, float a, float speed, OutputStream* notificationOutputStream) {
    // We multiply by 2, because, only one wheel rotates
    float angleRadius = angleDeciDegree * PI_DIVIDE_1800 * 2.0f;
    RobotKinematics* robotKinematics = getRobotKinematics();
    float rightWheelLengthForOnePulse = getRightWheelLengthForOnePulse(robotKinematics);
    float wheelsDistanceFromCenter = getWheelsDistanceFromCenter(robotKinematics);

    float realDistanceLeft = (wheelsDistanceFromCenter * angleRadius) / rightWheelLengthForOnePulse;
    gotoSimplePosition(pidMotion, realDistanceLeft, 0.0f, a, speed, notificationOutputStream);
}

// SIMPLEST FUNCTION

// -> Go / Back

float forwardSimpleMM(PidMotion* pidMotion, float distanceInMM, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getMotionParameters(MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD);
    return forwardMM(pidMotion, distanceInMM, motionParameter->a, motionParameter->speed, notificationOutputStream);
}

float backwardSimpleMM(PidMotion* pidMotion, float distanceInMM, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getMotionParameters(MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD);
    return backwardMM(pidMotion, distanceInMM, motionParameter->a, motionParameter->speed, notificationOutputStream);
}

// -> Left / Right

float leftSimpleDeciDegree(PidMotion* pidMotion, float angleDeciDegree, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getMotionParameters(MOTION_PARAMETER_TYPE_ROTATION);
    return leftDeciDegree(pidMotion, angleDeciDegree, motionParameter->a, motionParameter->speed, notificationOutputStream);
}

float rightSimpleDeciDegree(PidMotion* pidMotion, float angleDeciDegree, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getMotionParameters(MOTION_PARAMETER_TYPE_ROTATION);
    return rightDeciDegree(pidMotion, angleDeciDegree, motionParameter->a, motionParameter->speed, notificationOutputStream);
}

// -> Left / Right : One Wheel

void leftOneWheelSimpleDeciDegree(PidMotion* pidMotion, float angleDeciDegree, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getMotionParameters(MOTION_PARAMETER_TYPE_ROTATION_ONE_WHEEL);
    leftOneWheelDeciDegree(pidMotion, angleDeciDegree, motionParameter->a, motionParameter->speed, notificationOutputStream);
}

void rightOneWheelSimpleDeciDegree(PidMotion* pidMotion, float angleDeciDegree, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getMotionParameters(MOTION_PARAMETER_TYPE_ROTATION_ONE_WHEEL);
    rightOneWheelDeciDegree(pidMotion, angleDeciDegree, motionParameter->a, motionParameter->speed, notificationOutputStream);
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

float leftSimpleDeciDegreeAndWait(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream) {
    leftSimpleDeciDegree(pidMotion, angleDegree, notificationOutputStream);
    handleAndWaitFreeMotion(pidMotion);
    return angleDegree;
}

float rightSimpleDeciDegreeAndWait(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream) {
    rightSimpleDeciDegree(pidMotion, angleDegree, notificationOutputStream);
    handleAndWaitFreeMotion(pidMotion);
    return -angleDegree;
}
