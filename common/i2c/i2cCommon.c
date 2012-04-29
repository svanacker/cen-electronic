#include <i2c.h>

#include "i2cCommon.h"

#include "../../common/commons.h"

void WaitI2C() {
#ifndef MPBLAB_SIMULATION
    IdleI2C();
#endif
}
