#include <math.h>
#include <stdlib.h>
#include "motion.h"

#include "../../common/commons.h"

#include "../../common/delay/delay30F.h"

#include "../../common/io/buffer.h"
#include "../../common/io/outputStream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/math/cenMath.h"

#include "../extended/bsplineDebug.h"

#include "../pid/pid.h"
#include "../pid/pidDebug.h"
#include "../pid/alphaTheta.h"
#include "../pid/pidMotionProfileComputer.h"
#include "../pid/bSplinePidComputer.h"

#include "../position/coders.h"
#include "../position/trajectory.h"

#include "../../device/motor/pwmMotor.h"
#include "../../device/motion/simple/motionDevice.h"

#include "../../main/motorBoard/motorBoard.h"
#include "../../robot/robotConstants.h"

// MOTION PARAMETERS

/** The parameters for motion. */
static MotionParameter defaultMotionParameters[MOTION_PARAMETERS_COUNT];

MotionParameter* getDefaultMotionParameters(unsigned char motionType) {
    return &defaultMotionParameters[motionType];
}

// MAIN FUNCTIONS

/**
 * Stop the robot.
 */
void stopPosition(BOOL maintainPositionValue) {
    updateTrajectoryAndClearCoders();

    if (maintainPositionValue) {
		// TODO : will not work with new system
        maintainPosition();
    } else {
        // Avoid that robot reachs his position, and stops the motors
        clearMotionDefinitionList();
    }
	// Avoid that the robot considered he will remain the initial speed for next move (it is stopped).
	clearInitialSpeeds();

    stopMotors();
}

void maintainPosition(void) {
    gotoPosition(0.0f, 0.0f, 0.0f, 0.0f);
}

unsigned char handleInstructionAndMotion(void) {
    updateCoders();
    updateTrajectory();

    // OPTIONAL
    // checkCoders();

    // MANDATORY

    unsigned char value = updateMotors();

    Buffer* buffer = getI2CSlaveOutputBuffer();
    OutputStream* outputStream = getOutputStream(buffer);
	OutputStream* debugOutputStream = getDebugOutputStreamLogger();

    if (value == NO_POSITION_TO_REACH) {
        // don't do anything
    }
    if (value == POSITION_TO_MAINTAIN) {
        // does not end
    } else if (value == POSITION_IN_PROGRESS) {
        // don't do anything, wait
    } else if (value == POSITION_REACHED) {
        notifyReached(outputStream);
		notifyReached(debugOutputStream);

        stopPosition(TRUE);
    } else if (value == POSITION_BLOCKED_WHEELS) {
        notifyFailed(outputStream);
		notifyFailed(debugOutputStream);
        stopPosition(TRUE);
    } else if (value == POSITION_OBSTACLE) {
        notifyObstacle(outputStream);
        stopPosition(TRUE);
    }
    return value;
}

unsigned char handleAndWaitFreeMotion(void) {
    unsigned char value = -1;
    while (TRUE) {
        value = handleInstructionAndMotion();
        // POSITION_BLOCKED_WHEELS is not necesseray because we block the position after
        if (value == NO_POSITION_TO_REACH || value == POSITION_TO_MAINTAIN || value == POSITION_OBSTACLE) {
            // if (value == NO_POSITION_TO_REACH || value == POSITION_OBSTACLE) {
            appendString(getDebugOutputStreamLogger(), "hdlAndWaitFreeMotion->break=");
            appendDec(getDebugOutputStreamLogger(), value);
            break;
        }
    }
    return value;
}

void handleAndWaitMSec(unsigned long delayMs) {
    unsigned long DELAY = 10;
    unsigned long counter;
    for (counter = 0; counter < delayMs; counter += DELAY) {
        delaymSec(DELAY);
        handleInstructionAndMotion();
    }
}

unsigned char getMotionType(float left, float right) {
    if (floatEqualsZero(left) && floatEqualsZero(right)) {
        return MOTION_TYPE_MAINTAIN_POSITION;
    } else if (left <= 0.0f && right >= 0.0f) {
        return MOTION_TYPE_ROTATION;
    } else if (left >= 0.0f && right <= 0.0f) {
        return MOTION_TYPE_ROTATION;
    } else {
        return MOTION_TYPE_FORWARD_OR_BACKWARD;
    }
}

unsigned char getPidType(unsigned char motionType) {
    if (motionType == MOTION_TYPE_FORWARD_OR_BACKWARD) {
        return PID_TYPE_GO_INDEX;
    } else if (motionType == MOTION_TYPE_ROTATION) {
        return PID_TYPE_ROTATE_INDEX;
    } else if (motionType == MOTION_TYPE_MAINTAIN_POSITION) {
        return PID_TYPE_MAINTAIN_POSITION_INDEX;
    }
    // Default value, must not enter here
    return PID_TYPE_GO_INDEX;
}

// ---------------------------------------------------- STANDARD MOTION ---------------------------------------------

/**
 * Go to a position;
 */
void gotoPosition(float left, float right, float a, float speed) {
	PidMotionDefinition* nextMotionDefinition = getPidMotionDefinitionToWrite(); 

	if (getPidMotion()->currentMotionDefinition == NULL) {
		initForNextMotionDefinition();
		getPidMotion()->currentMotionDefinition = nextMotionDefinition;
	}

    // determine the type of motion
    unsigned char motionType = getMotionType(left, right);
    // determine the pidType to execute motionType
    unsigned char pidType = getPidType(motionType);


    // Alpha / Theta
    float theta = computeTheta(left, right);
    float alpha = computeAlpha(left, right);
    setNextPosition(nextMotionDefinition, INSTRUCTION_THETA_INDEX, motionType, pidType, theta, (float) a, (float) speed);
    setNextPosition(nextMotionDefinition, INSTRUCTION_ALPHA_INDEX, motionType, pidType, alpha, (float) a, (float) speed);

    //OutputStream* outputStream = getDebugOutputStreamLogger();
    //printInst(outputStream, getMotionInstruction(INSTRUCTION_THETA_INDEX));
    //printInst(outputStream, getMotionInstruction(INSTRUCTION_ALPHA_INDEX));
}

// ---------------------------------------------------- SPLINE MOTION ---------------------------------------------

/**
* @private
* Computes the best speed for the bspline, and take into consideration the derivative value (to avoid a too big speed)
*/
float computeBestSpeedForBSpline(BSplineCurve* curve, float speed) {
	float result = (speed * curve->speedFactor) / MOTION_SPEED_FACTOR_MAX;
	
	return result;
}

/**
* @private
* Computes the best acceleration for the bspline, and take into consideration the derivative value (to avoid a too big acceleration)
*/
float computeBestAccelerationForBSpline(BSplineCurve* curve, float a) {
	float result = (a * curve->accelerationFactor) / MOTION_ACCELERATION_FACTOR_MAX;
	return result;
}

/**
 * @private
 * Goto a position using a spline.
 */
void gotoSpline(PidMotionDefinition* motionDefinition) {
	OutputStream* outputStream = getDebugOutputStreamLogger();

	BSplineCurve* curve = &(motionDefinition->curve);
	writeBSplineControlPoints(outputStream, curve, WHEEL_AVERAGE_LENGTH);

    float curveLength = computeBSplineArcLength(curve, BSPLINE_TIME_INCREMENT);
	
	// debug
	// writeBSpline(getDebugOutputStreamLogger(), curve);

    // determine the type of motion
    unsigned char motionType = getMotionType(curveLength, curveLength);
    // determine the pidType to execute motionType
    unsigned char pidType = getPidType(motionType);

    // do as if we follow a straight line
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_TYPE_FORWARD_OR_BACKWARD);
	float bestA = computeBestAccelerationForBSpline(curve, motionParameter->a);
	float bestSpeed = computeBestSpeedForBSpline(curve, motionParameter->speed);

    setNextPosition(motionDefinition, INSTRUCTION_THETA_INDEX, motionType, pidType, curveLength, bestA, bestSpeed);
    setNextPosition(motionDefinition, INSTRUCTION_ALPHA_INDEX, motionType, pidType, 0.0f, motionParameter->a, motionParameter->speed);

	motionDefinition->computeU = &bSplineMotionUCompute;
}

/**
* @private
*/
void updateSimpleSplineWithDistance(BSplineCurve* curve,
									float destX, float destY, 
									float destAngle, 
									float distance1, float distance2, 
									unsigned char accelerationFactor, unsigned char speedFactor,
									BOOL relative) {
	// If the distance of the control point is negative, we considerer that we go back
	BOOL backward = distance1 < 0.0f;

	Position* position = getPosition();
	// scale coordinates
	float x = position->pos.x;
	float y = position->pos.y;
	float a = position->orientation;
	float xScaled = x  / WHEEL_AVERAGE_LENGTH;
	float yScaled = y  / WHEEL_AVERAGE_LENGTH;

	// For P0-P1
	float c1 = cosf(a);
    float s1 = sinf(a);

	float dca1 = (distance1 * c1);
	float dsa1 = (distance1 * s1);

	// For P2-P3
	float c2 = cosf(destAngle);
    float s2 = sinf(destAngle);

	float dca2 = (distance2 * c2);
	float dsa2 = (distance2 * s2);

    // Update the bspline curve
	// P0
    resetBSplineCurve(curve, xScaled, yScaled, backward);
	curve->accelerationFactor = accelerationFactor;
	curve->speedFactor = speedFactor;

	// P1
	Point* point = &(curve->p1);
	// P1 along x axis
	point->x = (x + dca1);
	point->y = (y + dsa1);
	scale(point, WHEEL_AVERAGE_LENGTH);
	
	if (relative) {	

		// P2
		point = &(curve->p2);
		//rotate(point, a, (destX - x - dca2), (destY - y - dsa2));
		rotate(point, a, (destX - dca2), (destY - dsa2));
		point->x += x;
		point->y += y;

		// P3
		point = &(curve->p3);
		//rotate(point, a, (destX - x), (destY - y));
		rotate(point, a, (destX), (destY));
		point->x += x;
		point->y += y;
	}
	else {
		// P2
		point = &(curve->p2);
		point->x = (destX - dca2);
		point->y = (destY - dsa2);

		// P3
		point = &(curve->p3);
		point->x = destX;
		point->y = destY;
	}
	// Scale points
	scale(&(curve->p2), WHEEL_AVERAGE_LENGTH);
	scale(&(curve->p3), WHEEL_AVERAGE_LENGTH);
}


/**
 * Goto a position from the current position, with a certain distance to do the angle
 */
void gotoSimpleSpline(float destX, float destY,
					  float destAngle, 
					  float controlPointDistance1, float controlPointDistance2,
					  unsigned int accelerationFactor, unsigned int speedFactor,
					  BOOL relative) {
	// Append to the next motion definition list
	PidMotionDefinition* nextMotionDefinition = getPidMotionDefinitionToWrite(); 
	
	// goto the current motion definition if no one is in progress
	if (getPidMotion()->currentMotionDefinition == NULL) {
		initForNextMotionDefinition();
		getPidMotion()->currentMotionDefinition = nextMotionDefinition;
	}

	BSplineCurve* curve = &(nextMotionDefinition->curve);

	updateSimpleSplineWithDistance(curve,
									destX, destY,
									destAngle,
									controlPointDistance1, controlPointDistance2,
									accelerationFactor, speedFactor,
									relative);
//	OutputStream* outputStream = getDebugOutputStreamLogger();
//	println(outputStream);

	gotoSpline(nextMotionDefinition);
}


// PULSE FUNCTIONS

// -> Go/Back

float forwardSimple(float pulse) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_TYPE_FORWARD_OR_BACKWARD);
    gotoPosition(pulse, pulse, motionParameter->a, motionParameter->speed);
    return pulse;
}

float backwardSimple(float pulse) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_TYPE_FORWARD_OR_BACKWARD);
    gotoPosition(-pulse, pulse, motionParameter->a, motionParameter->speed);
    return -pulse;
}

// -> Rotation

float leftSimple(float pulse) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_TYPE_ROTATION);
    gotoPosition(-pulse, pulse, motionParameter->a, motionParameter->speed);
    return -pulse;
}

float rightSimple(float pulse) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_TYPE_ROTATION);
    gotoPosition(pulse, pulse, motionParameter->a, motionParameter->speed);
    return pulse;
}

// -> OneWheel

float leftOneWheelSimple(float pulse) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_TYPE_ROTATION_ONE_WHEEL);
    gotoPosition(0, pulse, motionParameter->a, motionParameter->speed);
    return pulse;
}

float rightOneWheelSimple(float pulse) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_TYPE_ROTATION_ONE_WHEEL);
    gotoPosition(pulse, 0, motionParameter->a, motionParameter->speed);
    return pulse;
}

// MM OR DEGREE FUNCTIONS

float forwardMM(float distanceInMM, float a, float speed) {
    float realDistanceLeft = distanceInMM / WHEEL_LENGTH_LEFT;
    float realDistanceRight = distanceInMM / WHEEL_LENGTH_RIGHT;

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
    float realDistanceLeft = -(WHEELS_DISTANCE_FROM_CENTER * angleRadius) / WHEEL_LENGTH_LEFT;
    float realDistanceRight = (WHEELS_DISTANCE_FROM_CENTER * angleRadius) / WHEEL_LENGTH_RIGHT;
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
    long realDistanceRight = (WHEELS_DISTANCE_FROM_CENTER * angleRadius) / WHEEL_LENGTH_LEFT;
    gotoPosition(0.0f, realDistanceRight, a, speed);
}

void rightOneWheelDegree(float angleDegree, float a, float speed) {
    // We multiply by 2, because, only one wheel rotates
    float angleRadius = angleDegree * PI_DIVIDE_1800 * 2.0f;
    long realDistanceLeft = (WHEELS_DISTANCE_FROM_CENTER * angleRadius) / WHEEL_LENGTH_RIGHT;
    gotoPosition(realDistanceLeft, 0.0f, a, speed);
}

// SIMPLEST FUNCTION

// -> Go / Back

float forwardSimpleMM(float distanceInMM) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_TYPE_FORWARD_OR_BACKWARD);
    return forwardMM(distanceInMM, motionParameter->a, motionParameter->speed);
}

float backwardSimpleMM(float distanceInMM) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_TYPE_FORWARD_OR_BACKWARD);
    return backwardMM(distanceInMM, motionParameter->a, motionParameter->speed);
}

// -> Left / Right

float leftSimpleDegree(float angleDegree) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_TYPE_ROTATION);
    return leftDegree(angleDegree, motionParameter->a, motionParameter->speed);
}

float leftSimpleMilliDegree(float angleMilliDegree) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_TYPE_ROTATION);
    return leftMilliDegree(angleMilliDegree, motionParameter->a, motionParameter->speed);
}

float rightSimpleDegree(float angleDegree) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_TYPE_ROTATION);
    return rightDegree(angleDegree, motionParameter->a, motionParameter->speed);
}

float rightSimpleMilliDegree(float angleMilliDegree) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_TYPE_ROTATION);
    return rightMilliDegree(angleMilliDegree, motionParameter->a, motionParameter->speed);
}

// -> Left / Right : One Wheel

void leftOneWheelSimpleDegree(float angleDegree) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_TYPE_ROTATION_ONE_WHEEL);
    leftOneWheelDegree(angleDegree, motionParameter->a, motionParameter->speed);
}

void rightOneWheelSimpleDegree(float angleDegree) {
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_TYPE_ROTATION_ONE_WHEEL);
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

// CALIBRATION

void squareCalibrationRotationLeft(BOOL inverse) {
	if (inverse) {
		rightSimpleDegreeAndWait(DEG_90);
	}
	else {
		leftSimpleDegreeAndWait(DEG_90);
	}
}

void squareCalibrationRotationRight(BOOL inverse) {
	if (inverse) {
		leftSimpleDegreeAndWait(DEG_90);
	}
	else {
		rightSimpleDegreeAndWait(DEG_90);
	}
}
void squareCalibrationLine(signed int x, signed int y, signed int angle, BOOL inverse) {
	signed char cp = 100.0f;
	if (inverse) {
		gotoSimpleSpline(x, -y, -angle, cp, cp, MOTION_ACCELERATION_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL, FALSE);
	}
	else {
		gotoSimpleSpline(x, y, angle, cp, cp, MOTION_ACCELERATION_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL, FALSE);
	}
	handleAndWaitFreeMotion();
}

void squareCalibration(unsigned char type, float lengthInMM) {
    // to the bottom middle
	signed int lengthInMM2 = lengthInMM / 2.0f;

	BOOL inverse = (type == 0);

	// turn on right
	squareCalibrationRotationRight(inverse);

	// to the bottom right
	squareCalibrationLine(0, -lengthInMM2, -900.0f, inverse);
    squareCalibrationRotationLeft(inverse);

    // to the top right
	squareCalibrationLine(lengthInMM, -lengthInMM2, 0.0f, inverse);
    squareCalibrationRotationLeft(inverse);

    // to the top left
	squareCalibrationLine(lengthInMM, lengthInMM2, 900.0f, inverse);
    squareCalibrationRotationLeft(inverse);

    // to the bottom left
	squareCalibrationLine(0, lengthInMM2, 1800.0f, inverse);
    squareCalibrationRotationLeft(inverse);

    // to the bottom middle
	squareCalibrationLine(0, 0, -900.0f, inverse);
    squareCalibrationRotationLeft(inverse);
}
