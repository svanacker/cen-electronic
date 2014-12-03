#include "testDriverTest.h"

#include <stdlib.h>

#include "../../../test/unity/unity.h"
#include "../../../common/error/error.h"
#include "../../../common/io/stream.h"

#include "../../../device/device.h"
#include "../../../device/deviceList.h"
#include "../../../device/test/testDevice.h"
#include "../../../device/test/testDeviceInterface.h"

#include "../../../drivers/dispatcher/driverDataDispatcherList.h"
#include "../../../drivers/dispatcher/localDriverDataDispatcher.h"
#include "../../../drivers/test/testDriver.h"

// Dispatchers
#define TEST_DRIVER_TEST_DATA_DISPATCHER_LIST_LENGTH 1
static DriverDataDispatcher driverDataDispatcherListArray[TEST_DRIVER_TEST_DATA_DISPATCHER_LIST_LENGTH];

// Drivers
#define TEST_DRIVER_TEST_REQUEST_DRIVER_BUFFER_LENGTH	10
static Buffer driverRequestBuffer;
static char driverRequestBufferArray[TEST_DRIVER_TEST_REQUEST_DRIVER_BUFFER_LENGTH];
#define TEST_DRIVER_TEST_RESPONSE_DRIVER_BUFFER_LENGTH	10
static Buffer driverResponseBuffer;
static char driverResponseBufferArray[TEST_DRIVER_TEST_RESPONSE_DRIVER_BUFFER_LENGTH];


// Devices
#define TEST_DRIVER_TEST_DEVICE_LIST_LENGTH		1
static Device deviceListArray[TEST_DRIVER_TEST_DEVICE_LIST_LENGTH];

void testDriverTestTestSuite(void) {
	RUN_TEST(test_testDriverGetValue);
}

void test_testDriverGetValue(void) {

	// Dispatchers
	initDriverDataDispatcherList((DriverDataDispatcher(*)[]) &driverDataDispatcherListArray, TEST_DRIVER_TEST_DATA_DISPATCHER_LIST_LENGTH);
	addLocalDriverDataDispatcher();

	// Init the drivers
	initDrivers(&driverRequestBuffer, &driverRequestBufferArray, TEST_DRIVER_TEST_REQUEST_DRIVER_BUFFER_LENGTH,
		&driverResponseBuffer, &driverResponseBufferArray, TEST_DRIVER_TEST_RESPONSE_DRIVER_BUFFER_LENGTH);

	// Get test driver for debug purpose
	addDriver(testDriverGetDescriptor(), TRANSMIT_LOCAL);

	// Devices
	initDeviceList(&deviceListArray, TEST_DRIVER_TEST_DEVICE_LIST_LENGTH);
	addLocalDevice(getTestDeviceInterface(), getTestDeviceDescriptor());

	int actual = testDriverGetValue(10, 20);

	TEST_ASSERT_EQUAL(30, actual);
}