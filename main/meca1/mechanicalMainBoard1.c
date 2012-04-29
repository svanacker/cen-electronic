#include <i2c.h>
#include <p30fxxxx.h>
#include <stdlib.h>

#include "mechanicalBoard1.h"

#include "../../common/setup/pic30FSetup.h"

#include "../../common/delay/delay30F.h"

#include "../../common/i2c/slave/i2cSlave.h"
#include "../../common/i2c/slave/i2cSlaveSetup.h"
#include "../../common/i2c/slave/i2cSlaveLink.h"

#include "../../common/io/filter.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/pin.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/stream.h"

#include "../../common/pwm/pwmPic.h"
#include "../../common/pwm/servoPwm.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/timer/timerList.h"

#include "../../device/device.h"
#include "../../device/dispatcher/deviceDataDispatcher.h"

// -> Devices

// Test
#include "../../device/test/deviceTest.h"
#include "../../device/test/deviceTestInterface.h"

// Servo
#include "../../device/servo/servoDevice.h"
#include "../../device/servo/servoDeviceInterface.h"

// Relay
#include "../../device/relay/relayDevice.h"
#include "../../device/relay/relayDeviceInterface.h"

// System
#include "../../device/system/systemDevice.h"
#include "../../device/system/systemDeviceInterface.h"

// Robot 2011
#include "../../robot/2011/pliersDevice2011.h"
#include "../../robot/2011/pliersDeviceInterface2011.h"

#include "../../drivers/driverStreamListener.h"

// The port for which we debug (we can send instruction too)
#define SERIAL_PORT_DEBUG 	SERIAL_PORT_2

/**
* Device list.
*/
static DeviceList devices;

// serial DEBUG 
static char debugInputBufferArray[MECA_BOARD_1_DEBUG_INPUT_BUFFER_LENGTH];
static Buffer debugInputBuffer;
static char debugOutputBufferArray[MECA_BOARD_1_DEBUG_OUTPUT_BUFFER_LENGTH];
static Buffer debugOutputBuffer;
static OutputStream debugOutputStream;
static StreamLink debugSerialStreamLink;

// logs
static LogHandler serialLogHandler;

// i2c Link
static char i2cSlaveInputBufferArray[MECA_BOARD_1_I2C_INPUT_BUFFER_LENGTH];
static Buffer i2cSlaveInputBuffer;
static char i2cSlaveOutputBufferArray[MECA_BOARD_1_I2C_OUTPUT_BUFFER_LENGTH];
static Buffer i2cSlaveOutputBuffer;
static StreamLink i2cSerialStreamLink;

// devices
static Device testDevice;
static Device systemDevice;
static Device servoDevice;
static Device relayDevice;

// Specific 2011
static Device pliersDevice;

void initDevicesDescriptor() {
	addLocalDevice(&testDevice, getTestDeviceInterface(), getTestDeviceDescriptor());
	addLocalDevice(&systemDevice, getSystemDeviceInterface(), getSystemDeviceDescriptor());
	addLocalDevice(&servoDevice, getServoDeviceInterface(), getServoDeviceDescriptor());
	addLocalDevice(&relayDevice, getRelayDeviceInterface(), getRelayDeviceDescriptor());

	addLocalDevice(&pliersDevice, getPliers2011DeviceInterface(), getPliers2011DeviceDescriptor());

	initDevices(&devices);
}

void initMechanicalBoard1Pins() {
	// by default, PORTB is as input, do not set it !
	PORTBbits.RB8 = 0;
	PORTBbits.RB9 = 0;
	PORTBbits.RB10 = 0;
	PORTBbits.RB11 = 0;
	PORTBbits.RB12 = 0;

	// PORTB as input
	// TRISB = 0x00FF;
	// TRISB = 0xFFFF;

	// PORT C as output (relay)
	TRISC = 0;
	PORTC = 0;
	TRISC = 0;

	// PORT D as output (relay)
	TRISD = 0;
	PORTD = 0;
	TRISD = 0;
}

int main(void) {
	initMechanicalBoard1Pins();
	openSerialLink(	&debugSerialStreamLink,
					&debugInputBuffer,
					&debugInputBufferArray,
					MECA_BOARD_1_DEBUG_INPUT_BUFFER_LENGTH,
					&debugOutputBuffer,
					&debugOutputBufferArray,
					MECA_BOARD_1_DEBUG_OUTPUT_BUFFER_LENGTH,
					&debugOutputStream,
					SERIAL_PORT_DEBUG);

	// Init the logs
	initLog(DEBUG);
	addLogHandler(&serialLogHandler, "UART", &debugOutputStream, DEBUG);
	appendString(getOutputStreamLogger(INFO), "MECHANICAL 1 OK");

	openSlaveI2cStreamLink(&i2cSerialStreamLink,
							&i2cSlaveInputBuffer,
							&i2cSlaveInputBufferArray,
							MECA_BOARD_1_I2C_INPUT_BUFFER_LENGTH,
							&i2cSlaveOutputBuffer,
							&i2cSlaveOutputBufferArray,
							MECA_BOARD_1_I2C_OUTPUT_BUFFER_LENGTH,
							MECHANICAL_BOARD_1_I2C_ADDRESS
						);

	// init the devices
	initDevicesDescriptor();
	setPicName("MECHANICAL 1");

	// Init the timers management
	startTimerList();

	// 2011 : TODO : A regarder
	ADPCFG = 0xFFFF;

	// printAllPinValues(getOutputStreamLogger(DEBUG));

	while (1) {

		// I2C Stream
		handleStreamInstruction(&i2cSlaveInputBuffer,
								&i2cSlaveOutputBuffer,
								NULL,
								&filterRemoveCRLF,
								NULL);

		// UART Stream
		handleStreamInstruction(&debugInputBuffer,
								&debugOutputBuffer,
								&debugOutputStream,
								&filterRemoveCRLF,
								NULL);
	}
	return (0);
}
