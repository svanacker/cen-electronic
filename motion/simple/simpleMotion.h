#ifndef SIMPLE_MOTION_H
#define SIMPLE_MOTION_H

// MAIN FUNCTIONS

#include <stdbool.h>
#include "../pid/pidMotion.h"

/**
 * Stop the robot.
 */
void stopPosition(PidMotion* pidMotion, bool maintainPositionValue);

/**
 * Ask the robot to maintain the position.
 */
void maintainPosition(PidMotion* pidMotion);

/**
 * Go to a position;
 */
void gotoPosition(PidMotion* pidMotion, float left, float right, float a, float speed);

/**
 * Go simply forward with a distance in pulse and returns the pulse.
 */
float forwardSimple(PidMotion* pidMotion, float pulse);

float backwardSimple(PidMotion* pidMotion, float pulse);

float leftSimple(PidMotion* pidMotion, float pulse);

float rightSimple(PidMotion* pidMotion, float pulse);

float leftOneWheelSimple(PidMotion* pidMotion, float pulse);

float rightOneWheelSimple(PidMotion* pidMotion, float pulse);

// Function with distance or degree

/**
 * Go Forward with a distance in mm.
 * @param a acceleration
 * @param speed
 */
float forwardMM(PidMotion* pidMotion, float distanceInMM, float a, float speed);

float backwardMM(PidMotion* pidMotion, float distanceInMM, float a, float speed);

/**
 * Do a rotation with an angle in the trigonometric turn.
 * @param angle in degree
 * @param a acceleration
 * @param speed
 */
float rotationDegree(PidMotion* pidMotion, float angleDegree, float a, float speed);

/**
 * Do a rotation with an angle in milliDegree in the trigonometric turn.
 * @param angle in milliDegree
 * @param a acceleration
 * @param speed
 */
float rotationMilliDegree(PidMotion* pidMotion, float milliAngleDegree, float a, float speed);

float leftDegree(PidMotion* pidMotion, float angleDegree, float a, float speed);

float leftMilliDegree(PidMotion* pidMotion, float milliAngleDegree, float a, float speed);

float rightDegree(PidMotion* pidMotion, float angleDegree, float a, float speed);

float rightMilliDegree(PidMotion* pidMotion, float milliAngleDegree, float a, float speed);

void leftOneWheelDegree(PidMotion* pidMotion, float angleDegree, float a, float speed);

void rightOneWheelDegree(PidMotion* pidMotion, float angleDegree, float a, float speed);

// Simplest function

/**
 * Go Forward with a distance in mm.
 */
float forwardSimpleMM(PidMotion* pidMotion, float distanceInMM);

float backwardSimpleMM(PidMotion* pidMotion, float distanceInMM);

float leftSimpleDegree(PidMotion* pidMotion, float angleDegree);

float leftSimpleMilliDegree(PidMotion* pidMotion, float milliAngleDegree);

float rightSimpleDegree(PidMotion* pidMotion, float angleDegree);

float rightSimpleMilliDegree(PidMotion* pidMotion, float milliAngleDegree);

void leftOneWheelSimpleDegree(PidMotion* pidMotion, float angleDegree);

void rightOneWheelSimpleDegree(PidMotion* pidMotion, float angleDegree);

// With Wait

float forwardSimpleMMAndWait(PidMotion* pidMotion, float distanceInMM);

float backwardSimpleMMAndWait(PidMotion* pidMotion, float distanceInMM);

float leftSimpleDegreeAndWait(PidMotion* pidMotion, float angleDegree);

float leftSimpleMilliDegreeAndWait(PidMotion* pidMotion, float milliAngleDegree);

float rightSimpleDegreeAndWait(PidMotion* pidMotion, float angleDegree);

float rightSimpleMilliDegreeAndWait(PidMotion* pidMotion, float milliAngleDegree);

#endif
