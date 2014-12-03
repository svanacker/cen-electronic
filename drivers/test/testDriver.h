#ifndef TEST_DRIVER_H
#define TEST_DRIVER_H

#include "../../drivers/driver.h"

/**
* Call to driverTest value.
* @param argument1 the argument1 which must be added with argument2
* @param argument2 the argument1 which must be added with argument1
* @return result the result of addition between argument1 and argument2
*/
signed int testDriverGetValue(signed int argument1, signed int argument2);

/**
* Get the test driver descriptor.
* @return the test driver descriptor
*/
DriverDescriptor* testDriverGetDescriptor();

#endif
