#include "../pc/i2cCommonPc.h"
#include "../i2cCommon.h"

void WaitI2C(I2cBus* i2cBus) {
    // Nothing to do
}

I2cBusConnectionPc* getI2cBusConnectionPc(I2cBusConnection* i2cBusConnection) {
    I2cBusConnectionPc* result = (I2cBusConnectionPc*)i2cBusConnection->object;
    return result;
}

