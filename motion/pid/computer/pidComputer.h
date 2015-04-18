#ifndef PID_COMPUTER_H
#define PID_COMPUTER_H

/** 
 * All Common Functions for Simple or BSpline Pid Compute.
 */

#include "../pid.h"
#include "../parameters/pidParameter.h"
#include "../pidMotionError.h"
#include "../motionInstruction.h"

/**
 * Compute the correction.
 * @param motionError all information about errors (for alpha and theta)
 * @param pid the PID which must be applied
 * @param normalSpeed the normal speed which must be reached
 * @param error the error which must be stored into motionError
 */
float computePidCorrection(PidMotionError* motionError,
                            PidParameter* pidParameter,
                            float normalSpeed,
                            float error);

/**
* Computes the normal position / distance at time.
* @param motionInstruction determines what was requested as motion
* @param time pidTime used to know where the robot must be (in terms of alpha / theta) value.
*/
float computeNormalPosition(MotionInstruction* motionInstruction, float time);

/**
 * Compute the normal speed at the specified pidTime
 * @param motionInstruction information about motion
 * @param time pidTime
 */
float computeNormalSpeed(MotionInstruction* motionInstruction, float time);


#endif

