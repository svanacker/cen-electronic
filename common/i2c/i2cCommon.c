#include "../../common/commons.h"

#ifdef PROG_32
	#include <p32xxxx.h>
#else
	#include <i2c.h>
#endif

#include "i2cCommon.h"

void WaitI2C() {
#ifndef MPLAB_SIMULATION
    IdleI2C();
#endif
}
