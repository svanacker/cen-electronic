#ifndef PID_COMPUTER_H
#define PID_COMPUTER_H

#include <stdbool.h>

/** 
 * All Common Functions for Simple or BSpline Pid Compute.
 */

#include "../pid.h"
#include "../parameters/pidParameter.h"
#include "../pidComputationInstructionValues.h"
#include "../motionInstruction.h"

/**
 * Compute the correction.
 * @param computationInstructionValues the values for a specific instruction
 * @param pid the PID which must be applied
 * @param normalSpeed the normal speed which must be reached
 * @param error the error which must be stored into motionError
 */
float computePidCorrection(PidComputationInstructionValues* computationInstructionValues,
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

/**
 * Compute the normal acceleration at the specified pidTime
 * @param motionInstruction information about motion
 * @param time pidTime
 */
float computeNormalAcceleration(MotionInstruction* inst, float time);

/**
 * Get the normal voltage value at the speed defined by the parameter
 * @param normalSpeed the speed for which we want the normal voltage
 * TODO : Must be Test By Experimentation
 */
float getNormalU(float normalSpeed);

// CONVERSION UTILS

float getUFactorAtFullSpeed(bool rotation);

#endif

