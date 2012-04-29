#ifndef DRIVER_TEST_H
#define DRIVER_TEST_H

#include "../../drivers/driver.h"
#include "../../drivers/dispatcher/DriverDataDispatcher.h"

/**
* Call to driverTest value.
*/
unsigned int driverTestGetValue(int argument);

/**
* Get a driver descriptor.
*/
DriverDescriptor* driverTestGetDescriptor();

#endif
