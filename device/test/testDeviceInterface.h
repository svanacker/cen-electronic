#ifndef TEST_DEVICE_INTERFACE_H
#define TEST_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/**
* Command header for test.
* The test is an addition between 2 values.
*/
#define COMMAND_TEST 't'

/**
* Command to notify information from the slave to the master and test it.
*/
#define COMMAND_NOTIFY_TEST 'T'

/**
* Interface for Test Device.
* @return the interface for Test Device
*/
DeviceInterface* getTestDeviceInterface();

#endif

