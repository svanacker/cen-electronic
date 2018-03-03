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
void gotoSimplePosition(PidMotion* pidMotion, float left, float right, float a, float speed, OutputStream* notificationOutputStream);

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
float rotationDeciDegree(PidMotion* pidMotion, float angleDeciDegree, float a, float speed, OutputStream* notificationOutputStream);

float leftDeciDegree(PidMotion* pidMotion, float angleDeciDegree, float a, float speed, OutputStream* notificationOutputStream);

float rightDeciDegree(PidMotion* pidMotion, float angleDeciDegree, float a, float speed, OutputStream* notificationOutputStream);

void leftOneWheelDeciDegree(PidMotion* pidMotion, float angleDeciDegree, float a, float speed, OutputStream* notificationOutputStream);

void rightOneWheelDeciDegree(PidMotion* pidMotion, float angleDeciDegree, float a, float speed, OutputStream* notificationOutputStream);

// Simplest function

/**
 * Go Forward with a distance in mm.
 */
float forwardSimpleMM(PidMotion* pidMotion, float distanceInMM, OutputStream* notificationOutputStream);

float backwardSimpleMM(PidMotion* pidMotion, float distanceInMM, OutputStream* notificationOutputStream);

float leftSimpleDeciDegree(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream);

float rightSimpleDeciDegree(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream);

void leftOneWheelSimpleDeciDegree(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream);

void rightOneWheelSimpleDeciDegree(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream);

// With Wait

float forwardSimpleMMAndWait(PidMotion* pidMotion, float distanceInMM, OutputStream* notificationOutputStream);

float backwardSimpleMMAndWait(PidMotion* pidMotion, float distanceInMM, OutputStream* notificationOutputStream);

float leftSimpleDeciDegreeAndWait(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream);

float rightSimpleDeciDegreeAndWait(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream);

#endif
