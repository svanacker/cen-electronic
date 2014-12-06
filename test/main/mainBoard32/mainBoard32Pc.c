#include "mainBoard32Pc.h"

#include <stdlib.h>

#include "../../../common/clock/clock.h"
#include "../../../common/error/error.h"
#include "../../../common/io/stream.h"
#include "../../../common/io/pc/consoleOutputStream.h"
#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"
#include "../../../common/log/pc/consoleLogHandler.h"

#include "../../../device/device.h"
#include "../../../device/deviceList.h"

#include "../../../device/clock/clockDevice.h"
#include "../../../device/clock/clockDeviceInterface.h"

#include "../../../device/test/testDevice.h"
#include "../../../device/test/testDeviceInterface.h"

#include "../../../device/motor/pwmMotorDevice.h"
#include "../../../device/motor/pwmMotorDeviceInterface.h"

#include "../../../drivers/clock/mockClock.h"
#include "../../../drivers/driverList.h"
#include "../../../drivers/dispatcher/driverDataDispatcherList.h"
#include "../../../drivers/dispatcher/localDriverDataDispatcher.h"
#include "../../../drivers/test/testDriver.h"

#include "../../../remote/clock/remoteClock.h"


// Dispatchers
#define MAIN_BOARD_32_PC_DATA_DISPATCHER_LIST_LENGTH 2
static DriverDataDispatcher driverDataDispatcherListArray[MAIN_BOARD_32_PC_DATA_DISPATCHER_LIST_LENGTH];

// Drivers
#define MAIN_BOARD_32_PC_REQUEST_DRIVER_BUFFER_LENGTH	40
static Buffer driverRequestBuffer;
static char driverRequestBufferArray[MAIN_BOARD_32_PC_REQUEST_DRIVER_BUFFER_LENGTH];
#define MAIN_BOARD_32_PC_RESPONSE_DRIVER_BUFFER_LENGTH	40
static Buffer driverResponseBuffer;
static char driverResponseBufferArray[MAIN_BOARD_32_PC_RESPONSE_DRIVER_BUFFER_LENGTH];


// Devices
#define MAIN_BOARD_32_PC_DEVICE_LIST_LENGTH		10
static Device deviceListArray[MAIN_BOARD_32_PC_DEVICE_LIST_LENGTH];

void runMainBoard32PC(void) {
	initLog(DEBUG);
	addConsoleLogHandler(DEBUG);

	// Dispatchers
	initDriverDataDispatcherList((DriverDataDispatcher(*)[]) &driverDataDispatcherListArray, MAIN_BOARD_32_PC_DATA_DISPATCHER_LIST_LENGTH);
	addLocalDriverDataDispatcher();

	// Init the drivers
	initDrivers(&driverRequestBuffer, (char(*)[]) &driverRequestBufferArray, MAIN_BOARD_32_PC_REQUEST_DRIVER_BUFFER_LENGTH,
		&driverResponseBuffer, (char(*)[]) &driverResponseBufferArray, MAIN_BOARD_32_PC_RESPONSE_DRIVER_BUFFER_LENGTH);

	// Get test driver for debug purpose
	addDriver(testDriverGetDescriptor(), TRANSMIT_LOCAL);

	// Devices
	initDeviceList((Device(*)[]) &deviceListArray, MAIN_BOARD_32_PC_DEVICE_LIST_LENGTH);
	addLocalDevice(getTestDeviceInterface(), getTestDeviceDescriptor());
}