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

I2cMasterBusPc* getMasterI2cBusPc(I2cBus* i2cBus) {
    I2cMasterBusPc* result = (I2cMasterBusPc*)i2cBus->object;
    return result;
}

void i2cMasterBusPcInitialize(I2cMasterBusPc* i2cMasterBusPc, LPCWSTR i2cPipeMasterName, LPCWSTR i2cPipeSlaveName) {
    if (i2cMasterBusPc == NULL) {
        appendString(getErrorOutputStreamLogger(), "i2cBus->object must be initialized");
        return;
    }
    // Avoid more than one initialization
    if (i2cMasterBusPc->masterPipeHandle != NULL) {
        appendString(getDebugOutputStreamLogger(), "I2C PC Master (Pipe) already initialized\n");
        return;
    }
    appendString(getDebugOutputStreamLogger(), "I2C Master Initialize\r\n");
    i2cMasterBusPc->masterPipeHandle = initServerPipe(i2cPipeMasterName);
    delaymSec(200);
    i2cMasterBusPc->slavePipeHandle = initClientPipe(i2cPipeSlaveName);
}

void i2cMasterInitialize(I2cBus* i2cBus) {
    I2cMasterBusPc* i2cMasterBusPc = getMasterI2cBusPc(i2cBus);
    if (i2cMasterBusPc == NULL) {
        appendString(getErrorOutputStreamLogger(), "i2cBus->object must be initialized by calling i2cMasterBusPcInitialize first !");
        return;
    }
}

void i2cMasterFinalize(I2cBus* i2cBus) {
    I2cMasterBusPc* i2cMasterBusPc = getMasterI2cBusPc(i2cBus);
    if (i2cMasterBusPc->masterPipeHandle != NULL) {
        portableMasterCloseI2C(i2cBus);
        CloseHandle(i2cMasterBusPc->masterPipeHandle);
    }
    if (i2cMasterBusPc->slavePipeHandle != NULL) {
        CloseHandle(i2cMasterBusPc->slavePipeHandle);
    }
}
