#include "../../../common/commons.h"

#include <peripheral/legacy/i2c_legacy.h>

#include "../i2cCommon.h"

void WaitI2C() {
    #ifndef MPLAB_SIMULATION
        IdleI2C1();
    #endif
}

inline void portableStartI2C() {
    StartI2C1();
}

inline void portableStopI2C() {
    StopI2C1();
}

inline void portableAckI2C() {
    AckI2C1();
}

inline void portableNackI2C() {
    NotAckI2C1();
}
