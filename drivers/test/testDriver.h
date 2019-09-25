#ifndef TEST_DRIVER_H
#define TEST_DRIVER_H

#include <stdbool.h>

#include "../../drivers/driver.h"

/**
* Call to driverTest value.
* @param argument1 the argument1 which must be added with argument2
* @param argument2 the argument1 which must be added with argument1
* @return result the result of addition between argument1 and argument2
*/
signed int testDriverGetValue(signed int argument1, signed int argument2);

/** 
* Intensive test of drivers.
* Try with several combination of number and verify that the result is good !
* @param tryCounter how many test we want to pass
*/
bool testDriverIntensive(unsigned int testCount);

/**
* Get the test driver descriptor.
* @return the test driver descriptor
*/
DriverDescriptor* testDriverGetDescriptor();

#endif
