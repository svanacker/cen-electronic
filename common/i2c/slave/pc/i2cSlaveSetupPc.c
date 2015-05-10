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

static I2cSlaveBusConnectionPc i2cSlaveBusConnectionPc;

I2cSlaveBusConnectionPc* getSlaveI2cBusConnectionPc(I2cBusConnection* i2cBusConnection) {
    I2cSlaveBusConnectionPc* result = (I2cSlaveBusConnectionPc*)i2cBusConnection->object;
    return result;
}

void i2cSlaveInitialize(I2cBusConnection* i2cBusConnection) {
    // Avoid more than one initialization
    if (i2cBusConnection->opened) {
        writeError(I2C_SLAVE_ALREADY_INITIALIZED);
        return;
    }
    i2cBusConnection->object = &i2cSlaveBusConnectionPc;

    appendString(getDebugOutputStreamLogger(), "I2C Slave Write Address=");
    appendHex2(getDebugOutputStreamLogger(), i2cBusConnection->i2cAddress);
    appendCRLF(getDebugOutputStreamLogger());

    i2cSlaveBusConnectionPc.masterToSlaveHandle = initClientPipe(L"\\\\.\\pipe\\mainBoardPipe");
    i2cSlaveBusConnectionPc.slaveToMasterHandle = initServerPipe(L"\\\\.\\pipe\\motorBoardPipe");
    i2cBusConnection->opened = true;

    // Thread : master => slave
    i2cSlaveBusConnectionPc.masterToSlaveThreadHandle = createStandardThread(
        masterToSlaveCallback,    // thread proc
        (LPVOID)i2cBusConnection,    // thread parameter 
        &(i2cSlaveBusConnectionPc.masterToSlaveThreadId));      // returns thread ID 

    // Thread : slave => master
    i2cSlaveBusConnectionPc.slaveToMasterThreadHandle = createStandardThread(
        slaveToMasterCallback,    // thread proc
        (LPVOID)i2cBusConnection,    // thread parameter 
        &(i2cSlaveBusConnectionPc.slaveToMasterThreadId));      // returns thread ID 
}

