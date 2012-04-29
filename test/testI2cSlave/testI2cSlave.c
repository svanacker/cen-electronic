#include <p30fxxxx.h>
#include <stdlib.h>

#include "../../common/setup/pic30FSetup.h"

#include "../../common/delay/delay30F.h"

#include "../../common/i2c/i2cDebug.h"
#include "../../common/i2c/slave/i2cSlave.h"
#include "../../common/i2c/slave/i2cSlaveSetup.h"
#include "../../common/i2c/slave/i2cSlaveLink.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/streamLink.h"

#include "../../common/log/logHandler.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"

#include "../../drivers/pcf/pcf8574.h"

// serial link DEBUG 
static Buffer debugInputBuffer;
static Buffer debugOutputBuffer;
static OutputStream debugOutputStream;
static StreamLink debugSerialStreamLink;

// logs
static LogHandler serialLogHandler;

// i2c Link
static Buffer i2cSlaveInputBuffer;
static Buffer i2cSlaveOutputBuffer;
static StreamLink i2cSerialStreamLink;

// I2C Debug
static Buffer debugI2cInputBuffer;
static Buffer debugI2cOutputBuffer;

#define TEST_I2C_ADDRESS 0x50

/**
* Test I2C_SLAVE
*/
void testI2CSlave() {
	unsigned char SERIAL_PORT_DEBUG = SERIAL_PORT_2;
	
	// Open the serial Link
	openSerialLink(	&debugSerialStreamLink,
					&debugInputBuffer,
					&debugOutputBuffer,
					&debugOutputStream,
					SERIAL_PORT_DEBUG);

	// Logs
	initLog(DEBUG);
	addLogHandler(&serialLogHandler, "UART", &debugOutputStream, DEBUG);
	appendString(getOutputStreamLogger(INFO), "TEST I2C SLAVE ");

	delaymSec(1000);

	// Debug of I2C
	initI2CDebugBuffers(&debugI2cInputBuffer, &debugI2cOutputBuffer);

	// I2C Slave
	openSlaveI2cStreamLink(&i2cSerialStreamLink,
							&i2cSlaveInputBuffer,
							&i2cSlaveOutputBuffer,
							TEST_I2C_ADDRESS);

	// Fill the buffer with a message for the master
	OutputStream* i2cSlaveOutputStream = getOutputStream(&i2cSlaveOutputBuffer);
	appendString(i2cSlaveOutputStream, "Hello From Slave");

	while (1) {
		delaymSec(1000);
		printI2cDebugBuffers();	
		delaymSec(1000);
		appendString(i2cSlaveOutputStream, "t50");
	}
}

/**
 * TEST FOR I2C SLAVE
 */
int main(void) {
	testI2CSlave();

	return 0;
}

