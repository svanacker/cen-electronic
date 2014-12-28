#ifndef TEST2_DEVICE_INTERFACE_H
#define TEST2_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/**
* Command header for test.
* The test is an addition between 2 values.
*/
#define COMMAND_TEST2 				   'w'

/** 
 * Command to do an intensive test for Test Driver.
 */
#define COMMAND_INTENSIVE_TEST_DRIVER 'I'

/**
* Interface for Test2 Device.
* @return the interface for Test Device
*/
DeviceInterface* getTest2DeviceInterface();

#endif

