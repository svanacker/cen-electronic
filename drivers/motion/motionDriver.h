#ifndef MOTION_DRIVER_H
#define MOTION_DRIVER_H

#include "../../common/commons.h"

#include "../../drivers/dispatcher/DriverDataDispatcher.h"

/**
* State to know if it's ready for Next Motion.
* @param value the new status
*/
void setReadyForNextMotion(BOOL value);

/**
* Returns if the state is ready.
* @return if the state is ready.
*/
BOOL isReadyForNextMotion();

/**
* Set the motion instruction index.
*/
void incMotionInstructionIndex();

/**
* Returns the index of motion instruction.
*/
unsigned int getMotionInstructionIndex();


/**
* Ask the motor to go to a position (pulse argument).
* @return TRUE if the driver answer
*/
BOOL motionDriverGotoPositionPulse(
					    			float left,
									float right,
									float a,
									float s );

/**
* Ask the motor to go forward for a distance in mm.
* @return TRUE if the driver answer
*/
BOOL motionDriverForward(float distanceInMM);

/**
* Ask to stay in place and use slavery to do it.
*/
BOOL motionDriverMaintainPosition();

/**
* Ask the motor to go backward for a distance in mm.
* @return TRUE if the driver answer
*/
BOOL motionDriverBackward(float distanceInMM);

/**
* Ask the motor to turn left for an angle in degree.
* @param leftDegree the angle to turn left
* @return TRUE if the driver answer
*/
BOOL motionDriverLeft(float leftDeciDegree);

/**
* Ask the motor to turn right for an angle in degree.
* @param rightDegree the angle to turn right
* @return TRUE if the driver answer
*/
BOOL motionDriverRight(float rightDeciDegree);

// ONE WHEEL

/**
* Ask the motor to turn left for an angle in degree (Right Wheel don't move).
* @param leftDegree the angle to turn left
* @return TRUE if the driver answer
*/
BOOL motionDriverOneWheelLeft(float leftDeciDegree);

/**
* Ask the motor to turn right for an angle in degree (Left Wheel don't move).
* @param rightDegree the angle to turn right
* @return TRUE if the driver answer
*/
BOOL motionDriverOneWheelRight(float rightDeciDegree);

// BSPLINE 

/**
 * Do a bspline curve using relative coordinates (x, y, angle)
 */
BOOL motionDriverBSplineRelative(float x, float y, float angle, float dist0, float dist1, int accelerationFactor, int speedFactor);

/**
 * Do a bspline curve using absolute coordinates (x, y, angle)
 */
BOOL motionDriverBSplineAbsolute(float x, float y, float angle, float dist0, float dist1, int accelerationFactor, int speedFactor);

// STOP

/**
* Ask to stop the motors (no position maintain)
* @return TRUE if the driver answer
*/
BOOL motionDriverStop();

/**
* Ask to stop the motors (with position maintain)
* @return TRUE if the driver answer
*/
BOOL motionDriverObstacle();

BOOL motionDriverLeftOneWheel(float leftDeciDegree);

BOOL motionDriverRightOneWheel(float rightDeciDegree);

BOOL motionSetParameters(int motionType, int a, int speed);

// TRAJECTORY

BOOL trajectoryDriverSetAbsolutePosition(float x, float y, float deciDegree);

#endif
