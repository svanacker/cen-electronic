#ifndef MOTION_DRIVER_H
#define MOTION_DRIVER_H

#include <stdbool.h>

#include "../../drivers/dispatcher/driverDataDispatcher.h"

/**
* State to know if it's ready for Next Motion.
* @param value the new status
*/
void setReadyForNextMotion(bool value);

/**
* Returns if the state is ready.
* @return if the state is ready.
*/
bool isReadyForNextMotion();

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
* @return true if the driver answer
*/
bool motionDriverGotoPositionPulse(
                                    float left,
                                    float right,
                                    float a,
                                    float s );

/**
* Ask the motor to go forward for a distance in mm.
* @return true if the driver answer
*/
bool motionDriverForward(float distanceInMM);

/**
* Ask to stay in place and use slavery to do it.
*/
bool motionDriverMaintainPosition();

/**
* Ask the motor to go backward for a distance in mm.
* @return true if the driver answer
*/
bool motionDriverBackward(float distanceInMM);

/**
* Ask the motor to turn left for an angle in degree.
* @param leftDegree the angle to turn left
* @return true if the driver answer
*/
bool motionDriverLeft(float leftDeciDegree);

/**
* Ask the motor to turn right for an angle in degree.
* @param rightDegree the angle to turn right
* @return true if the driver answer
*/
bool motionDriverRight(float rightDeciDegree);

// ONE WHEEL

/**
* Ask the motor to turn left for an angle in degree (Right Wheel don't move).
* @param leftDegree the angle to turn left
* @return true if the driver answer
*/
bool motionDriverOneWheelLeft(float leftDeciDegree);

/**
* Ask the motor to turn right for an angle in degree (Left Wheel don't move).
* @param rightDegree the angle to turn right
* @return true if the driver answer
*/
bool motionDriverOneWheelRight(float rightDeciDegree);

// BSPLINE 

/**
 * Do a bspline curve using relative coordinates (x, y, angle)
 */
bool motionDriverBSplineRelative(float x, float y, float angle, float dist0, float dist1, int accelerationFactor, int speedFactor);

/**
 * Do a bspline curve using absolute coordinates (x, y, angle)
 */
bool motionDriverBSplineAbsolute(float x, float y, float angle, float dist0, float dist1, int accelerationFactor, int speedFactor);

// STOP

/**
* Ask to stop the motors (no position maintain)
* @return true if the driver answer
*/
bool motionDriverStop();

/**
* Ask to stop the motors (with position maintain)
* @return true if the driver answer
*/
bool motionDriverObstacle();

bool motionDriverLeftOneWheel(float leftDeciDegree);

bool motionDriverRightOneWheel(float rightDeciDegree);

bool motionSetParameters(int motionType, int a, int speed);


#endif
