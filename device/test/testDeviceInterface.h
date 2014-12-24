#ifndef TEST_DEVICE_INTERFACE_H
#define TEST_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/**
* Command header for test.
* The test is an addition between 2 values.
*/
#define COMMAND_TEST 'w'

/**
 * Command header for big Test
 * The test is an addition of 10 values (to ensure that there is no overflow problems when sending lots of information).
 */
#define COMMAND_HEAVY_TEST 'W'

/**
* Command to notify information from the slave to the master and test it.
*/
#define COMMAND_NOTIFY_TEST 'n'

/**
* Interface for Test Device.
* @return the interface for Test Device
*/
DeviceInterface* getTestDeviceInterface();

#endif

