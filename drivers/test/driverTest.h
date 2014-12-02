#ifndef DRIVER_TEST_H
#define DRIVER_TEST_H

#include "../../drivers/driver.h"

/**
* Call to driverTest value.
* @param argument1 the argument1 which must be added with argument2
* @param argument2 the argument1 which must be added with argument1
* @return result the result of addition between argument1 and argument2
*/
signed int driverTestGetValue(signed int argument1, signed int argument2);

/**
* Get the test driver descriptor.
* @return the test driver descriptor
*/
DriverDescriptor* driverTestGetDescriptor();

#endif
