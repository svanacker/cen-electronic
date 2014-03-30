#ifndef MOTION_H
#define MOTION_H

#include "../../common/commons.h"

/**
 * Structure defining default Motion Parameters.
 */
typedef struct {
    /** The default acceleration. */
    float a;
    /** The default speed. */
    float speed;
} MotionParameter;

#define MOTION_PARAMETERS_COUNT			4

/**
 * The robot goes forward or backward.
 */
#define MOTION_TYPE_FORWARD_OR_BACKWARD	0x00

/**
 * The robot do a rotation.
 */
#define MOTION_TYPE_ROTATION			0x01

/**
 * The robot do a rotation with One Wheel
 */
#define MOTION_TYPE_ROTATION_ONE_WHEEL	0x02

/**
 * The robot must maintain a position.
 */
#define MOTION_TYPE_MAINTAIN_POSITION	0x03


// SPEED FACTOR

#define	MOTION_SPEED_FACTOR_MAX				15
#define	MOTION_SPEED_FACTOR_HIGH			10
#define	MOTION_SPEED_FACTOR_NORMAL			7
#define	MOTION_SPEED_FACTOR_LOW				4
#define	MOTION_SPEED_FACTOR_MIN				1

// ACCELERATION FACTOR

#define	MOTION_ACCELERATION_FACTOR_MAX		15
#define	MOTION_ACCELERATION_FACTOR_HIGH		10
#define	MOTION_ACCELERATION_FACTOR_NORMAL	7
#define	MOTION_ACCELERATION_FACTOR_LOW		4
#define	MOTION_ACCELERATION_FACTOR_MIN		1

// PARAMETERS

/**
 * Returns Parameters for Motion.
 */
MotionParameter* getDefaultMotionParameters(unsigned char motionType);

// HANDLING FUNCTION

/**
 * Handle function so the robot is aware of asking.
 */
unsigned char handleInstructionAndMotion(void);

/**
 * Wait after the end of a position, or a position which is maintained.
 */
unsigned char handleAndWaitFreeMotion(void);

/**
 * Handle and wait after a delay of milliseconds.
 * TODO : breaks if there is another instruction ???
 */
void handleAndWaitMSec(unsigned long delayMs);

// MAIN FUNCTIONS

/**
 * Stop the robot.
 */
void stopPosition(bool maintainPositionValue);

/**
 * Ask the robot to maintain the position.
 */
void maintainPosition(void);

/**
 * Go to a position;
 */
void gotoPosition(float left, float right, float a, float speed);

void updateSimpleSplineWithDistance(float destX, float destY,
									float destAngle,
									float distance1, float distance2,
									unsigned char accelerationFactor, unsigned char speedFactor,
									bool relative);

/**
 * Go from the relative destination to the initial Position of the robot
 * Computes the bezier Point so that the curve is not to huge
 * @param relativeDestX the relative X destination point
 * @param relativeDestY the relative Y destination point
 * @param relativeDestAngle the relative Angle 
 * @param controlPointDistance1 the distance of P0->P1. If egal to 0.0f, the 
 * system determines the best distance to avoid too huge curve
 * @param controlPointDistance2 the distance of P2->P3. If egal to 0.0f, the 
 * system determines the best distance to avoid too huge curve
 */
void gotoSimpleSpline(float relativeDestX,
					  float relativeDestY,
					  float relativeDestAngle,
					  float controlPointDistance1,
					  float controlPointDistance2,
					  unsigned int accelerationFactor,
					  unsigned int speedFactor,
					  bool relative
					);

/**
* Go to a spline with indication of maxDerivative which indicates how the curve is huge
*/
void gotoSpline();

// Function with pulse

/**
 * Go simply forward with a distance in pulse and returns the pulse.
 */
float forwardSimple(float pulse);

float backwardSimple(float pulse);

float leftSimple(float pulse);

float rightSimple(float pulse);

float leftOneWheelSimple(float pulse);

float rightOneWheelSimple(float pulse);

// Function with distance or degree

/**
 * Go Forward with a distance in mm.
 * @param a acceleration
 * @param speed
 */
float forwardMM(float distanceInMM, float a, float speed);

float backwardMM(float distanceInMM, float a, float speed);

/**
 * Do a rotation with an angle in the trigonometrique turn.
 * @param angle in degree
 * @param a acceleration
 * @param speed
 */
float rotationDegree(float angleDegree, float a, float speed);

/**
 * Do a rotation with an angle in milliDegree in the trigonometrique turn.
 * @param angle in milliDegree
 * @param a acceleration
 * @param speed
 */
float rotationMilliDegree(float milliAngleDegree, float a, float speed);

float leftDegree(float angleDegree, float a, float speed);

float leftMilliDegree(float milliAngleDegree, float a, float speed);

float rightDegree(float angleDegree, float a, float speed);

float rightMilliDegree(float milliAngleDegree, float a, float speed);

void leftOneWheelDegree(float angleDegree, float a, float speed);

void rightOneWheelDegree(float angleDegree, float a, float speed);

// Simplest function

/**
 * Go Forward with a distance in mm.
 */
float forwardSimpleMM(float distanceInMM);

float backwardSimpleMM(float distanceInMM);

float leftSimpleDegree(float angleDegree);

float leftSimpleMilliDegree(float milliAngleDegree);

float rightSimpleDegree(float angleDegree);

float rightSimpleMilliDegree(float milliAngleDegree);

void leftOneWheelSimpleDegree(float angleDegree);

void rightOneWheelSimpleDegree(float angleDegree);

// With Wait

float forwardSimpleMMAndWait(float distanceInMM);

float backwardSimpleMMAndWait(float distanceInMM);

float leftSimpleDegreeAndWait(float angleDegree);

float leftSimpleMilliDegreeAndWait(float milliAngleDegree);

float rightSimpleDegreeAndWait(float angleDegree);

float rightSimpleMilliDegreeAndWait(float milliAngleDegree);

// CALIBRATION

void squareCalibration(unsigned char type, float lengthInMM);

// UTILITY FUNCTIONS

/**
 * Determine the type of motion by analysis of left and right instruction.
 * @param left instruction for left wheel
 * @param right instruction for right wheel
 * @return a type of Motion (Ex: MOTION_TYPE_ROTATION)
 */
unsigned char getMotionType(float left, float right);

/**
 * Determines the type of pid which must be applied depending of the motionType.
 */
unsigned char getPidType(unsigned char motionType);

#endif
