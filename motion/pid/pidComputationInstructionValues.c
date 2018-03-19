#include "pidComputationInstructionValues.h"

void clearPidComputationInstructionValues(PidComputationInstructionValues* pidComputationInstructionValues) {
    pidComputationInstructionValues->historyWriteIndex = 0;
    pidComputationInstructionValues->historyCount = 0;

    // PID
    pidComputationInstructionValues->pidType = PID_TYPE_NONE;
        
    // POSITION / SPEED
    pidComputationInstructionValues->normalPosition = 0;
    pidComputationInstructionValues->currentPosition = 0;
    pidComputationInstructionValues->oldPosition = 0;

    pidComputationInstructionValues->normalSpeed = 0;
    pidComputationInstructionValues->currentSpeed = 0;

    pidComputationInstructionValues->normalAcceleration = 0;
    pidComputationInstructionValues->currentAcceleration = 0;

    // ERRORS
    pidComputationInstructionValues->previousError = 0;
    pidComputationInstructionValues->error = 0;
    pidComputationInstructionValues->derivativeError = 0;
    pidComputationInstructionValues->integralError = 0;

    // U
    pidComputationInstructionValues->u = 0;

    // Clear the history
    unsigned int i;
    for (i = 0; i < PID_HISTORY_ITEM_COUNT; i++) {
        // PID TIME
        pidComputationInstructionValues->pidTimeHistory[i] = 0;

        // PID TYPE
        pidComputationInstructionValues->pidTypeHistory[i] = PID_TYPE_NONE;
       
        // POSITION
        pidComputationInstructionValues->positionHistory[i] = 0;
        
        // SPEED
        pidComputationInstructionValues->speedHistory[i] = 0;

        // ACCELERATION
        pidComputationInstructionValues->accelerationHistory[i] = 0;
        
        // ERRORS
        pidComputationInstructionValues->errorHistory[i] = 0;
        pidComputationInstructionValues->derivativeErrorHistory[i] = 0;
        pidComputationInstructionValues->integralErrorHistory[i] = 0;
        
        // U
        pidComputationInstructionValues->uHistory[i] = 0;
    }
}

void storePidComputationInstructionValueHistory(PidComputationInstructionValues* pidComputationInstructionValues, float pidTimeInSecond) {
    unsigned int i = pidComputationInstructionValues->historyWriteIndex;
    
    // PID TIME
    pidComputationInstructionValues->pidTimeHistory[i] = pidTimeInSecond;

    // PID TYPE
    pidComputationInstructionValues->pidTypeHistory[i] = pidComputationInstructionValues->pidType;

    // POSITION
    pidComputationInstructionValues->positionHistory[i] = pidComputationInstructionValues->currentPosition;

    // ACCELERATION
    pidComputationInstructionValues->accelerationHistory[i] = pidComputationInstructionValues->currentAcceleration;

    // SPEED
    pidComputationInstructionValues->speedHistory[i] = pidComputationInstructionValues->currentSpeed;

    // ERRORS
    pidComputationInstructionValues->errorHistory[i] = pidComputationInstructionValues->error;
    pidComputationInstructionValues->derivativeErrorHistory[i] = pidComputationInstructionValues->derivativeError;
    pidComputationInstructionValues->integralErrorHistory[i] = pidComputationInstructionValues->integralError;

    // U
    pidComputationInstructionValues->uHistory[i] = pidComputationInstructionValues->u;

    // For next time
    pidComputationInstructionValues->historyWriteIndex++;
    if (pidComputationInstructionValues->historyWriteIndex >= PID_HISTORY_ITEM_COUNT) {
        // Restart to 0
        pidComputationInstructionValues->historyWriteIndex = 0;
    }
    else {
        if (pidComputationInstructionValues->historyCount < PID_HISTORY_ITEM_COUNT) {
            pidComputationInstructionValues->historyCount++;
        }
    }
}