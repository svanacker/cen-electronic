#ifndef MOTION_H
#define MOTION_H

#include <stdbool.h>
#include "../parameters/motionParameterType.h"
#include "../pid/detectedMotionType.h"

// SPEED FACTOR

#define    MOTION_SPEED_FACTOR_MAX                15
#define    MOTION_SPEED_FACTOR_HIGH               10
#define    MOTION_SPEED_FACTOR_NORMAL            7
#define    MOTION_SPEED_FACTOR_LOW                4
#define    MOTION_SPEED_FACTOR_MIN                1

// ACCELERATION FACTOR

#define    MOTION_ACCELERATION_FACTOR_MAX        15
#define    MOTION_ACCELERATION_FACTOR_HIGH        10
#define    MOTION_ACCELERATION_FACTOR_NORMAL    7
#define    MOTION_ACCELERATION_FACTOR_LOW        4
#define    MOTION_ACCELERATION_FACTOR_MIN        1

// HANDLING FUNCTION

/**
 * Handle function so the robot is aware of asking.
 */
enum DetectedMotionType handleInstructionAndMotion(void);

/**
 * Wait after the end of a position, or a position which is maintained.
 */
enum DetectedMotionType handleAndWaitFreeMotion(void);

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

#endif
