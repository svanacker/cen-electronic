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
    pidComputationInstructionValues->normalU = 0;
    pidComputationInstructionValues->u = 0;

    // Status
    pidComputationInstructionValues->statusHistory->absAccelerationTooHighThanExpected = false;
    pidComputationInstructionValues->statusHistory->absSpeedTooLowThanExpected = false;
    pidComputationInstructionValues->statusHistory->absUTooHighThanExpected = false;
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

    // Status
    pidComputationInstructionValues->statusHistory[i].absAccelerationTooHighThanExpected = pidComputationInstructionValues->status.absAccelerationTooHighThanExpected;
    pidComputationInstructionValues->statusHistory[i].absSpeedTooLowThanExpected = pidComputationInstructionValues->status.absSpeedTooLowThanExpected;
    pidComputationInstructionValues->statusHistory[i].absUTooHighThanExpected = pidComputationInstructionValues->status.absUTooHighThanExpected;

    // For next time
    pidComputationInstructionValues->historyWriteIndex++;
    if (pidComputationInstructionValues->historyWriteIndex >= PID_HISTORY_ITEM_COUNT) {
        // Restart to 0
        pidComputationInstructionValues->historyWriteIndex = 0;
    } else {
        if (pidComputationInstructionValues->historyCount < PID_HISTORY_ITEM_COUNT) {
            pidComputationInstructionValues->historyCount++;
        }
    }
}