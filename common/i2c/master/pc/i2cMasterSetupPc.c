#include <stdbool.h>

#include "i2cMasterSetupPc.h"

#include "../i2cMasterSetup.h"

#include "../../../../common/i2c/i2cCommon.h"
#include "../../../../common/delay/cenDelay.h"
#include "../../../../common/i2c/master/i2cMaster.h"

#include "../../../../common/log/logger.h"
#include "../../../../common/log/logLevel.h"
#include "../../../../common/io/printWriter.h"

#include "../../../../common/pc/pipe/pipeServerHelper.h"

#include <Windows.h>

#define PIPE_I2C_MASTER_NAME    L"\\\\.\\pipe\\mainBoardPipe"
#define PIPE_I2C_SLAVE_NAME    L"\\\\.\\pipe\\motorBoardPipe"

static I2cMasterBusPc i2cMasterBusPc;

I2cMasterBusPc* getMasterI2cBusPc(I2cBus* i2cBus) {
    I2cMasterBusPc* result = (I2cMasterBusPc*)i2cBus->object;
    return result;
}

void i2cMasterInitialize(I2cBus* i2cBus) {
    i2cBus->object = &i2cMasterBusPc;
    // Avoid more than one initialization
    if (i2cMasterBusPc.masterPipeHandle != NULL) {
        appendString(getDebugOutputStreamLogger(), "I2C PC Master (Pipe) already initialized\n");
        return;
    }
    appendString(getDebugOutputStreamLogger(), "I2C Master Initialize\r\n");
    i2cMasterBusPc.masterPipeHandle = initServerPipe(PIPE_I2C_MASTER_NAME);
    delaymSec(200);
    i2cMasterBusPc.slavePipeHandle = initClientPipe(PIPE_I2C_SLAVE_NAME);
}

void i2cMasterFinalize(I2cBus* i2cBus) {
    if (i2cMasterBusPc.masterPipeHandle != NULL) {
        portableCloseI2C(i2cBus);
        CloseHandle(i2cMasterBusPc.masterPipeHandle);
    }
    if (i2cMasterBusPc.slavePipeHandle != NULL) {
        CloseHandle(i2cMasterBusPc.slavePipeHandle);
    }
}
