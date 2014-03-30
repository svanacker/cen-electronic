#include "../../common/commons.h"

#ifdef PROG_32
	#include <legacy/i2c_legacy.h>
#else
	#include <i2c.h>
#endif

#include "i2cCommon.h"

void WaitI2C() {
#ifndef MPLAB_SIMULATION
	#ifdef PROG_32
		IdleI2C1();
	#else
		IdleI2C();
	#endif
#endif
}

inline void portableStartI2C() {
	#ifdef PROG_32
		StartI2C1();
	#else
		StartI2C();
	#endif
}

inline void portableStopI2C() {
	#ifdef PROG_32
		StopI2C1();
	#else
		StopI2C();
	#endif
}
