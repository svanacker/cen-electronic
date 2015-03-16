#ifndef SIMPLE_MOTION_H
#define SIMPLE_MOTION_H

// MAIN FUNCTIONS

#include <stdbool.h>

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
 * Do a rotation with an angle in the trigonometric turn.
 * @param angle in degree
 * @param a acceleration
 * @param speed
 */
float rotationDegree(float angleDegree, float a, float speed);

/**
 * Do a rotation with an angle in milliDegree in the trigonometric turn.
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
