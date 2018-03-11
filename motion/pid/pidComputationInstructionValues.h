#ifndef PID_COMPUTATION_INSTRUCTION_VALUES_H
#define PID_COMPUTATION_INSTRUCTION_VALUES_H

#include "pidConstants.h"

/**
 * Defines a struct which stores :
 * - position / speed with associated history
 * - different errors and associated history
 * - u (voltage for pwm) and associated history)
 */
typedef struct PidComputationInstructionValues {
    /** Current index in which we must write next values (for historic values) */
    /** We use the array as a circular buffer, so we lost some values if the motion instruction is too long .*/
	unsigned int historyWriteIndex;
    /** How many history Values are stored . */
    unsigned int historyCount;
    /** The history of pid Time */
    float pidTimeHistory[PID_HISTORY_ITEM_COUNT];

    // PID TYPE
    enum PidType pidType;
    /** The history of pid Type */
    enum PidType pidTypeHistory[PID_HISTORY_ITEM_COUNT];
    
    // POSITION / SPEED
    /** Normal position. */
    float normalPosition;
    /** current position values. */
    float currentPosition;
    /** History of current Position */
    float positionHistory[PID_HISTORY_ITEM_COUNT];
    /** Old Position values. */
    float oldPosition;
    
    /** Normal Speed*/
    float normalSpeed;
    /** Speed. */
    float currentSpeed;
    /** History of speed */
    float speedHistory[PID_HISTORY_ITEM_COUNT];
    
    // ERRORS
    /** Stores the previous error */
    float previousError;
    
    /** The error between normal speed and real speed */
    float error;
    /** The history of the error */
    float errorHistory[PID_HISTORY_ITEM_COUNT];
    
    /** The derivative error between normal speed and real speed */
    float derivativeError;
    /** The history of the derivative error */
    float derivativeErrorHistory[PID_HISTORY_ITEM_COUNT];
    
    /** The integral error between normal speed and real speed */
    float integralError;
    /** The history of the integral error */
    float integralErrorHistory[PID_HISTORY_ITEM_COUNT];

    // U
    /** U (voltage) values. */
    float u;
    /** History of U */
    float uHistory[PID_HISTORY_ITEM_COUNT];
} PidComputationInstructionValues;

/**
 * Clear all current values so that we will be sure not to keep some old values from the previous Pid.
 * @param pidComputationValues
 */
void clearPidComputationInstructionValues(PidComputationInstructionValues* pidComputationInstructionValues);

/**
* Store a snapshot on all current values (position, normalPosition, speed, error, derivativeError ...)
*/
void storePidComputationInstructionValueHistory(PidComputationInstructionValues* pidComputationInstructionValues, float pidTimeInSecond);

#endif