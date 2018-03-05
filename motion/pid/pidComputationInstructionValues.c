#include "pidComputationInstructionValues.h"

void clearPidComputationInstructionValues(PidComputationInstructionValues* pidComputationInstructionValues) {
    pidComputationInstructionValues->historyWriteIndex = 0;
        
    // POSITION / SPEED
    pidComputationInstructionValues->normalPosition = 0;
    pidComputationInstructionValues->currentPosition = 0;
    pidComputationInstructionValues->oldPosition = 0;

    pidComputationInstructionValues->normalSpeed = 0;
    pidComputationInstructionValues->currentSpeed = 0;

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
       
        // POSITION
        pidComputationInstructionValues->positionHistory[i] = 0;
        
        // SPEED
        pidComputationInstructionValues->speedHistory[i] = 0;
        
        // ERRORS
        pidComputationInstructionValues->errorHistory[i] = 0;
        pidComputationInstructionValues->derivativeErrorHistory[i] = 0;
        pidComputationInstructionValues->integralErrorHistory[i] = 0;
        
        // U
        pidComputationInstructionValues->uHistory[i] = 0;
    }
}