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

void i2cSlaveInitialize(I2cBusConnection* i2cBusConnection) {
    // Avoid more than one initialization
    if (i2cBusConnection->opened) {
        writeError(I2C_SLAVE_ALREADY_INITIALIZED);
        return;
    }
    I2cBusConnectionPc* i2cBusConnectionPc = getI2cBusConnectionPc(i2cBusConnection);
    if (i2cBusConnectionPc == NULL) {
        writeError(I2C_BUS_CONNECTION_OBJECT_NULL);
    }

    OutputStream* logOutputStream = getInfoOutputStreamLogger();
    appendString(logOutputStream, "I2C Slave Write Address=");
    appendHex2(logOutputStream, i2cBusConnection->i2cAddress);
    appendCRLF(logOutputStream);

    i2cBusConnectionPc->masterToSlaveHandle = initClientPipe(i2cBusConnectionPc->i2cPipeMasterName);
    i2cBusConnectionPc->slaveToMasterHandle = initServerPipe(i2cBusConnectionPc->i2cPipeSlaveName);
    i2cBusConnection->opened = true;

    // Thread : master => slave
    i2cBusConnectionPc->masterToSlaveThreadHandle = createStandardThread(
        masterToSlaveCallback,    // thread proc
        (LPVOID)i2cBusConnection,    // thread parameter 
        &(i2cBusConnectionPc->masterToSlaveThreadId));      // returns thread ID 

    // Thread : slave => master
    i2cBusConnectionPc->slaveToMasterThreadHandle = createStandardThread(
        slaveToMasterCallback,    // thread proc
        (LPVOID)i2cBusConnection,    // thread parameter 
        &(i2cBusConnectionPc->slaveToMasterThreadId));      // returns thread ID 
}

