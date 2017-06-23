#include <i2c.h>

#include "../i2cCommon.h"

void WaitI2C(I2cBus* i2cBus) {
    IdleI2C();
}

void portableStartI2C(I2cBusConnection* i2cBusConnection) {
    StartI2C();
}

void portableStopI2C(I2cBusConnection* i2cBusConnection) {
    StopI2C();
}

void portableAckI2C(I2cBusConnection* i2cBusConnection) {
    AckI2C();
}

void portableNackI2C(I2cBusConnection* i2cBusConnection) {
    NotAckI2C();
}
