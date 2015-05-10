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
#include "../../../../common/pc/thread/threadHelper.h"

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

    appendString(getDebugOutputStreamLogger(), "I2C Slave Write Address=");
    appendHex2(getDebugOutputStreamLogger(), writeAddress);
    appendCRLF(getDebugOutputStreamLogger());

    masterToSlaveHandle = initClientPipe(L"\\\\.\\pipe\\mainBoardPipe");
    slaveToMasterHandle = initServerPipe(L"\\\\.\\pipe\\motorBoardPipe");
    initialized = true;

    // Thread : master => slave
    masterToSlaveThreadHandle = createStandardThread(
        masterToSlaveCallback,    // thread proc
        (LPVOID)masterToSlaveHandle,    // thread parameter 
        &masterToSlaveThreadId);      // returns thread ID 

    // Thread : slave => master
    slaveToMasterThreadHandle = createStandardThread(
        slaveToMasterCallback,    // thread proc
        (LPVOID)slaveToMasterHandle,    // thread parameter 
        &slaveToMasterThreadId);      // returns thread ID 
}

