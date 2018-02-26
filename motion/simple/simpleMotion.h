#ifndef SIMPLE_MOTION_H
#define SIMPLE_MOTION_H

// MAIN FUNCTIONS

#include <stdbool.h>
#include "../pid/pidMotion.h"

#include "../../common/io/outputStream.h"

/**
 * Stop the robot.
 */
void stopPosition(PidMotion* pidMotion, bool maintainPositionValue, OutputStream* notificationOutputStreaam);

/**
 * Ask the robot to maintain the position.
 */
void maintainPosition(PidMotion* pidMotion, OutputStream* notificationOutputStreaam);

/**
 * Go to a position;
 */
void gotoPosition(PidMotion* pidMotion, float left, float right, float a, float speed, OutputStream* notificationOutputStream);

/**
 * Go simply forward with a distance in pulse and returns the pulse.
 */
float forwardSimple(PidMotion* pidMotion, float pulse, OutputStream* notificationOutputStream);

float backwardSimple(PidMotion* pidMotion, float pulse, OutputStream* notificationOutputStream);

float leftSimple(PidMotion* pidMotion, float pulse, OutputStream* notificationOutputStream);

float rightSimple(PidMotion* pidMotion, float pulse, OutputStream* notificationOutputStream);

float leftOneWheelSimple(PidMotion* pidMotion, float pulse, OutputStream* notificationOutputStream);

float rightOneWheelSimple(PidMotion* pidMotion, float pulse, OutputStream* notificationOutputStream);

// Function with distance or degree

/**
 * Go Forward with a distance in mm.
 * @param a acceleration
 * @param speed
 */
float forwardMM(PidMotion* pidMotion, float distanceInMM, float a, float speed, OutputStream* notificationOutputStream);

float backwardMM(PidMotion* pidMotion, float distanceInMM, float a, float speed, OutputStream* notificationOutputStream);

/**
 * Do a rotation with an angle in the trigonometric turn.
 * @param angle in degree
 * @param a acceleration
 * @param speed
 */
float rotationDegree(PidMotion* pidMotion, float angleDegree, float a, float speed, OutputStream* notificationOutputStream);

/**
 * Do a rotation with an angle in milliDegree in the trigonometric turn.
 * @param angle in milliDegree
 * @param a acceleration
 * @param speed
 */
float rotationMilliDegree(PidMotion* pidMotion, float milliAngleDegree, float a, float speed, OutputStream* notificationOutputStream);

float leftDegree(PidMotion* pidMotion, float angleDegree, float a, float speed, OutputStream* notificationOutputStream);

float leftMilliDegree(PidMotion* pidMotion, float milliAngleDegree, float a, float speed, OutputStream* notificationOutputStream);

float rightDegree(PidMotion* pidMotion, float angleDegree, float a, float speed, OutputStream* notificationOutputStream);

float rightMilliDegree(PidMotion* pidMotion, float milliAngleDegree, float a, float speed, OutputStream* notificationOutputStream);

void leftOneWheelDegree(PidMotion* pidMotion, float angleDegree, float a, float speed, OutputStream* notificationOutputStream);

void rightOneWheelDegree(PidMotion* pidMotion, float angleDegree, float a, float speed, OutputStream* notificationOutputStream);

// Simplest function

/**
 * Go Forward with a distance in mm.
 */
float forwardSimpleMM(PidMotion* pidMotion, float distanceInMM, OutputStream* notificationOutputStream);

float backwardSimpleMM(PidMotion* pidMotion, float distanceInMM, OutputStream* notificationOutputStream);

float leftSimpleDegree(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream);

float leftSimpleMilliDegree(PidMotion* pidMotion, float milliAngleDegree, OutputStream* notificationOutputStream);

float rightSimpleDegree(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream);

float rightSimpleMilliDegree(PidMotion* pidMotion, float milliAngleDegree, OutputStream* notificationOutputStream);

void leftOneWheelSimpleDegree(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream);

void rightOneWheelSimpleDegree(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream);

// With Wait

float forwardSimpleMMAndWait(PidMotion* pidMotion, float distanceInMM, OutputStream* notificationOutputStream);

float backwardSimpleMMAndWait(PidMotion* pidMotion, float distanceInMM, OutputStream* notificationOutputStream);

float leftSimpleDegreeAndWait(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream);

float leftSimpleMilliDegreeAndWait(PidMotion* pidMotion, float milliAngleDegree, OutputStream* notificationOutputStream);

float rightSimpleDegreeAndWait(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream);

float rightSimpleMilliDegreeAndWait(PidMotion* pidMotion, float milliAngleDegree, OutputStream* notificationOutputStream);

#endif
