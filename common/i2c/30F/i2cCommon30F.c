#include <i2c.h>

#include "../i2cCommon.h"

void WaitI2C(I2cBus* i2cBus) {
    IdleI2C();
}

void portableStartI2C(I2cBus* i2cBus) {
    StartI2C();
}

void portableStopI2C(I2cBus* i2cBus) {
    StopI2C();
}

void portableAckI2C(I2cBus* i2cBus) {
    AckI2C();
}

void portableNackI2C(I2cBus* i2cBus) {
    NotAckI2C();
}
