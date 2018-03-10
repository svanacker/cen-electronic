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
void gotoSimplePosition(PidMotion* pidMotion, float leftMM, float rightMM, float a, float speed, OutputStream* notificationOutputStream);

// Function with distance or degree

/**
 * Go Forward with a distance in mm.
 * @param a acceleration
 * @param speed
 */
void forwardMM(PidMotion* pidMotion, float distanceInMM, float a, float speed, OutputStream* notificationOutputStream);

void backwardMM(PidMotion* pidMotion, float distanceInMM, float a, float speed, OutputStream* notificationOutputStream);

/**
 * Do a rotation with an angle in the trigonometric turn.
 * @param angle in degree
 * @param a acceleration
 * @param speed
 */
void rotationDegree(PidMotion* pidMotion, float angleDegree, float a, float speed, OutputStream* notificationOutputStream);

void leftDegree(PidMotion* pidMotion, float angleDegree, float a, float speed, OutputStream* notificationOutputStream);

void rightDegree(PidMotion* pidMotion, float angleDegree, float a, float speed, OutputStream* notificationOutputStream);

void leftOneWheelDegree(PidMotion* pidMotion, float angleDegree, float a, float speed, OutputStream* notificationOutputStream);

void rightOneWheelDegree(PidMotion* pidMotion, float angleDegree, float a, float speed, OutputStream* notificationOutputStream);

// Simplest function

/**
 * Go Forward with a distance in mm.
 */
void forwardSimpleMM(PidMotion* pidMotion, float distanceInMM, OutputStream* notificationOutputStream);

void backwardSimpleMM(PidMotion* pidMotion, float distanceInMM, OutputStream* notificationOutputStream);

void leftSimpleDegree(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream);

void rightSimpleDegree(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream);

void leftOneWheelSimpleDegree(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream);

void rightOneWheelSimpleDegree(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream);

// With Wait

void forwardSimpleMMAndWait(PidMotion* pidMotion, float distanceInMM, OutputStream* notificationOutputStream);

void backwardSimpleMMAndWait(PidMotion* pidMotion, float distanceInMM, OutputStream* notificationOutputStream);

void leftSimpleDegreeAndWait(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream);

void rightSimpleDegreeAndWait(PidMotion* pidMotion, float angleDegree, OutputStream* notificationOutputStream);

#endif
