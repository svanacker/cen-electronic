#ifndef PID_COMPUTER_H
#define PID_COMPUTER_H

#include "pid.h"

/**
 * Compute the correction.
 * @param motionError
 * @param pid
 * @param normalSpeed 
 * @param error the error which must be stored into motionError
 */
float computePidCorrection(MotionError* motionError,
        Pid* pid,
        float normalSpeed,
        float error);

/**
* Computes the normal position / distance at time
*/
float computeNormalPosition(MotionInstruction* motionInstruction, float time);

/**
 * Compute the normal speed at the specified pidTime
 * @param motionInstruction information about motion
 * @param time pidTime
 */
float computeNormalSpeed(MotionInstruction* motionInstruction, float time);

/**
 * Simple implementation of motion (go, back, rotation)
 */
void simpleMotionUCompute();

#endif

