#include "i2cSlaveSetupPc.h"
#include "i2cSlavePc.h"
#include "i2cSlaveInterruptPc.h"
#include "../i2cSlaveSetup.h"

#include "../../../../common/commons.h"
#include "../../../../common/delay/cenDelay.h"

#include "../../../../common/error/error.h"

#include "../../../../common/i2c/i2cCommon.h"

#include "../../../../common/io/printWriter.h"
#include "../../../../common/io/binaryPrintWriter.h"
#include "../../../../common/log/logger.h"
#include "../../../../common/log/logLevel.h"

#include "../../../../common/pc/pipe/pipeClientHelper.h"
#include "../../../../common/pc/pipe/pipeServerHelper.h"

#include <Windows.h>

static HANDLE masterToSlaveHandle;
static HANDLE masterToSlaveThreadHandle;
static DWORD  masterToSlaveThreadId = 0;

static HANDLE slaveToMasterHandle;
static HANDLE slaveToMasterThreadHandle;
static DWORD  slaveToMasterThreadId = 0;

static bool initialized = false;
static slaveWriteAddress = 0;


HANDLE getI2CMasterToSlaveHandle() {
    return masterToSlaveHandle;
}

HANDLE getI2CSlaveToMasterHandle() {
    return slaveToMasterHandle;
}

unsigned char getI2cWriteAddress(I2cBus* i2cBus) {
    return slaveWriteAddress;
}

unsigned char getI2cReadAddress(I2cBus* i2cBus) {
    return slaveWriteAddress | 1;
}

void i2cSlaveInitialize(I2cBus* i2cBus, unsigned char writeAddress) {
    // Avoid more than one initialization
    if (initialized) {
        writeError(I2C_SLAVE_ALREADY_INITIALIZED);
        return;
    }
    slaveWriteAddress = writeAddress;

    appendString(getOutputStreamLogger(DEBUG), "I2C Slave Write Address=");
    appendHex2(getOutputStreamLogger(DEBUG), writeAddress);
    appendCRLF(getOutputStreamLogger(DEBUG));

    masterToSlaveHandle = initClientPipe(L"\\\\.\\pipe\\mainBoardPipe");
    slaveToMasterHandle = initServerPipe(L"\\\\.\\pipe\\motorBoardPipe");
    initialized = true;

    // Create a thread to handle master to slave data
    masterToSlaveThreadHandle = CreateThread(
        NULL,              // no security attribute 
        0,                 // default stack size 
        masterToSlaveCallback,    // thread proc
        (LPVOID)masterToSlaveHandle,    // thread parameter 
        0,                 // not suspended 
        &masterToSlaveThreadId);      // returns thread ID 

    if (masterToSlaveThreadHandle == NULL)
    {
        printf("CreateThread failed, lastError=%d.\n", GetLastError());
    }

    slaveToMasterThreadHandle = CreateThread(
        NULL,              // no security attribute 
        0,                 // default stack size 
        slaveToMasterCallback,    // thread proc
        (LPVOID)slaveToMasterHandle,    // thread parameter 
        0,                 // not suspended 
        &slaveToMasterThreadId);      // returns thread ID 

    if (masterToSlaveThreadHandle == NULL)
    {
        printf("CreateThread failed, lastError=%d.\n", GetLastError());
    }
}

