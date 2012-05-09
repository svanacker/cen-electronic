#include <i2c.h>

#include "i2cCommon.h"

#include "../../common/commons.h"

void WaitI2C() {
#ifndef MPLAB_SIMULATION
    IdleI2C();
#endif
}
