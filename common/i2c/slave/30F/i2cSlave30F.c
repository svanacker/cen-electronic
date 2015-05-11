#include "../i2cSlave.h"

#include <i2c.h>

#include "../../../../common/i2c/i2cCommon.h"

unsigned char portableSlaveReadI2C(I2cBusConnection* i2cBusConnection) {
    unsigned char result = SlaveReadI2C();
    return result;
}

void portableSlaveWriteI2C(I2cBusConnection* i2cBusConnection, unsigned char c) {
    SlaveWriteI2C(c);
}
