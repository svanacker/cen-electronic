#include "../../../common/commons.h"

#include <i2c.h>

#include "../i2cCommon.h"

void WaitI2C() {
#ifndef MPLAB_SIMULATION
    IdleI2C();
#endif
}

inline void portableStartI2C() {
    StartI2C1();
}

inline void portableStopI2C() {
    StopI2C();
}
