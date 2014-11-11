#ifndef DEVICE_TEST_INTERFACE_H
#define DEVICE_TEST_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"


/**
* Command header for test.
*/
#define COMMAND_TEST 't'

/**
* Command to notify information from the slave to the master and test it.
*/
#define COMMAND_NOTIFY_TEST 'T'

/**
* Interface for Device
*/
DeviceInterface* getTestDeviceInterface();

#endif

