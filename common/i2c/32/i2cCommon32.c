#include "../../../common/commons.h"

#include <peripheral/legacy/i2c_legacy.h>

#include "../i2cCommon.h"

void WaitI2C() {
    IdleI2C1();
}

void portableStartI2C() {
    StartI2C1();
}

void portableStopI2C() {
    StopI2C1();
}

void portableAckI2C() {
    AckI2C1();
}

void portableNackI2C() {
    NotAckI2C1();
}
