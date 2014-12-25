#include "../../../common/commons.h"

#include <i2c.h>

#include "../i2cCommon.h"

void WaitI2C() {
    IdleI2C();
}

void portableStartI2C() {
    StartI2C();
}

void portableStopI2C() {
    StopI2C();
}

void portableAckI2C() {
    AckI2C();
}

void portableNackI2C() {
    NotAckI2C();
}
