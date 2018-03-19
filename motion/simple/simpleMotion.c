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
void gotoSimplePosition(PidMotion* pidMotion, float leftMM, float rightMM, float a, float speed, OutputStream* notificationOutputStream) {
	// determine the type of motion
	enum MotionParameterType motionParameterType = getMotionParameterType(leftMM, rightMM);

	// Alpha / Theta
	float thetaNextPosition = computeTheta(leftMM, rightMM);
	float alphaNextPosition = computeAlpha(leftMM, rightMM);

	PidMotionDefinition* motionDefinition = pidMotionGetNextToWritePidMotionDefinition(pidMotion);
	motionDefinition->motionType = MOTION_TYPE_NORMAL;
	motionDefinition->notificationOutputStream = notificationOutputStream;

	setNextPosition(motionDefinition, THETA, motionParameterType, thetaNextPosition, a, speed);
	setNextPosition(motionDefinition, ALPHA, motionParameterType, alphaNextPosition, a, speed);

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

// MM OR DEGREE FUNCTIONS

void forwardMM(PidMotion* pidMotion, float distanceInMM, float a, float speed, OutputStream* notificationOutputStream) {
    // Go at a position in millimeter
    gotoSimplePosition(pidMotion, distanceInMM, distanceInMM, a, speed, notificationOutputStream);
}

void backwardMM(PidMotion* pidMotion, float distanceInMM, float a, float speed, OutputStream* notificationOutputStream) {
    // Go at a position in millimeter
    forwardMM(pidMotion, -distanceInMM, a, speed, notificationOutputStream);
}

void rotationDegree(PidMotion* pidMotion, float angleDegree, float a, float speed, OutputStream* notificationOutputStream) {
    RobotKinematics* robotKinematics = getRobotKinematics();
    float leftMM = rotationInDegreeToRealDistanceForLeftWheel(robotKinematics, angleDegree);
    float rightMM = rotationInDegreeToRealDistanceForRightWheel(robotKinematics, angleDegree);

    gotoSimplePosition(pidMotion, leftMM, rightMM, a, speed, notificationOutputStream);
}

// -> rotation left/right

void leftDegree(PidMotion* pidMotion, float angleDegree, float a, float speed, OutputStream* notificationOutputStream) {
    rotationDegree(pidMotion, angleDegree, a, speed, notificationOutputStream);
}

void rightDegree(PidMotion* pidMotion, float angleDegree, float a, float speed, OutputStream* notificationOutputStream) {
    rotationDegree(pidMotion, -angleDegree, a, speed, notificationOutputStream);
}

// -> rotation one Wheel

void leftOneWheelDegree(PidMotion* pidMotion, float angleDegree, float a, float speed, OutputStream* notificationOutputStream) {
    // We multiply by 2, because, only one wheel rotates
    float angleRadius = degToRad(angleDegree) * 2.0f;
    RobotKinematics* robotKinematics = getRobotKinematics();
    float leftWheelLengthForOnePulse = getCoderLeftWheelLengthForOnePulse(robotKinematics);
    float wheelsDistanceFromCenter = getCoderWheelsDistanceFromCenter(robotKinematics);

    float realDistanceRight = (wheelsDistanceFromCenter * angleRadius) / leftWheelLengthForOnePulse;
    gotoSimplePosition(pidMotion, 0.0f, realDistanceRight, a, speed, notificationOutputStream);
}

void rightOneWheelDegree(PidMotion* pidMotion, float angleDegree, float a, float speed, OutputStream* notificationOutputStream) {
    // We multiply by 2, because, only one wheel rotates
    float angleRadius = degToRad(angleDegree) * 2.0f;
    RobotKinematics* robotKinematics = getRobotKinematics();
    float rightWheelLengthForOnePulse = getCoderRightWheelLengthForOnePulse(robotKinematics);
    float wheelsDistanceFromCenter = getCoderWheelsDistanceFromCenter(robotKinematics);

    float realDistanceLeft = (wheelsDistanceFromCenter * angleRadius) / rightWheelLengthForOnePulse;
    gotoSimplePosition(pidMotion, realDistanceLeft, 0.0f, a, speed, notificationOutputStream);
}

// SIMPLEST FUNCTION

// -> Go / Back

void forwardSimpleMM(PidMotion* pidMotion, float distanceInMM, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getMotionParameters(MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD);
    forwardMM(pidMotion, distanceInMM, motionParameter->a, motionParameter->speed, notificationOutputStream);
}

void backwardSimpleMM(PidMotion* pidMotion, float distanceInMM, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getMotionParameters(MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD);
    backwardMM(pidMotion, distanceInMM, motionParameter->a, motionParameter->speed, notificationOutputStream);
}

// -> Left / Right

void leftSimpleDegree(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getMotionParameters(MOTION_PARAMETER_TYPE_ROTATION);
    leftDegree(pidMotion, angleDegree, motionParameter->a, motionParameter->speed, notificationOutputStream);
}

void rightSimpleDegree(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getMotionParameters(MOTION_PARAMETER_TYPE_ROTATION);
    rightDegree(pidMotion, angleDegree, motionParameter->a, motionParameter->speed, notificationOutputStream);
}

// -> Left / Right : One Wheel

void leftOneWheelSimpleDegree(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getMotionParameters(MOTION_PARAMETER_TYPE_ROTATION_ONE_WHEEL);
    leftOneWheelDegree(pidMotion, angleDegree, motionParameter->a, motionParameter->speed, notificationOutputStream);
}

void rightOneWheelSimpleDegree(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream) {
    MotionParameter* motionParameter = getMotionParameters(MOTION_PARAMETER_TYPE_ROTATION_ONE_WHEEL);
    rightOneWheelDegree(pidMotion, angleDegree, motionParameter->a, motionParameter->speed, notificationOutputStream);
}

// With Wait

void forwardSimpleMMAndWait(PidMotion* pidMotion, float distanceInMM, OutputStream* notificationOutputStream) {
    forwardSimpleMM(pidMotion, distanceInMM, notificationOutputStream);
    handleAndWaitFreeMotion(pidMotion);
}

void backwardSimpleMMAndWait(PidMotion* pidMotion, float distanceInMM, OutputStream* notificationOutputStream) {
    backwardSimpleMM(pidMotion, distanceInMM, notificationOutputStream);
    handleAndWaitFreeMotion(pidMotion);
}

void leftSimpleDegreeAndWait(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream) {
    leftSimpleDegree(pidMotion, angleDegree, notificationOutputStream);
    handleAndWaitFreeMotion(pidMotion);
}

void rightSimpleDegreeAndWait(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream) {
    rightSimpleDegree(pidMotion, angleDegree, notificationOutputStream);
    handleAndWaitFreeMotion(pidMotion);
}
