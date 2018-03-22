#include "../pc/i2cCommonPc.h"
#include "../i2cCommon.h"

#include "../../delay/cenDelay.h"

#include "../../pc/pipe/pipeClientHelper.h"
#include "../../pc/pipe/pipeServerHelper.h"

#include <stdbool.h>
#include <windows.h>

void WaitI2C(I2cBus* i2cBus) {
    // Nothing to do
}

I2cBusConnectionPc* getI2cBusConnectionPc(I2cBusConnection* i2cBusConnection) {
    I2cBusConnectionPc* result = (I2cBusConnectionPc*)i2cBusConnection->object;
    return result;
}

void initI2cBusConnectionPc(I2cBusConnection* i2cBusConnection, I2cBus* i2cBus, I2cBusConnectionPc* i2cBusConnectionPc, unsigned char slaveAddress, LPCWSTR i2cPipeMasterName, LPCWSTR i2cPipeSlaveName) {
    if (!checkI2cBusConnectionNotNull(i2cBusConnection)) {
        return;
    }
    if (!checkI2cBusNotNull(i2cBus)) {
        return;
    }
    checkI2cBus(i2cBus);

    i2cBusConnection->i2cBus = i2cBus;
    i2cBusConnection->i2cAddress = slaveAddress;

    i2cBusConnection->object = i2cBusConnectionPc;
    i2cBusConnectionPc->i2cPipeMasterName = i2cPipeMasterName;

    if (i2cPipeMasterName != NULL) {
        i2cBusConnectionPc->masterToSlaveHandle = initServerPipe(i2cPipeMasterName);
    }
    else {
        // TODO : Write Error
    }
//    delaymSec(500);

    i2cBusConnectionPc->i2cPipeSlaveName = i2cPipeSlaveName;
    if (i2cPipeSlaveName != NULL) {
        i2cBusConnectionPc->slaveToMasterHandle = initClientPipe(i2cPipeSlaveName);
    }
    else {
        // TODO : Write Error
    }
}