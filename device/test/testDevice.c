#include "testDevice.h"
#include "testDeviceInterface.h"

#include <stdbool.h>

#include "../../common/cmd/commonCommand.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../device/device.h"

void deviceTestInit(void) {
}

void deviceTestShutDown(void) {
}

bool deviceTestIsOk(void) {
    return true;
}

void deviceTestHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    if (header == COMMAND_TEST) {
        int arg1 = readHex2(inputStream);
        int arg2 = readHex2(inputStream);
        int result = arg1 + arg2;

		ackCommand(outputStream, TEST_DEVICE_HEADER, COMMAND_TEST);
        // data
        appendHex2(outputStream, result);
    }
    else if (header == COMMAND_SIMPLE_TEST) {
		ackCommand(outputStream, TEST_DEVICE_HEADER, COMMAND_SIMPLE_TEST);
    }
	else if (header == COMMAND_HEAVY_TEST) {
		int arg1 = readHex2(inputStream);
		int arg2 = readHex2(inputStream);
		int arg3 = readHex4(inputStream);
		int arg4 = readHex4(inputStream);
		int arg5 = readHex2(inputStream);
		// Separator
		readHex(inputStream);
		int arg7 = readHex2(inputStream);
		int arg8 = readHex4(inputStream);
		long arg9 = (long) readHex6(inputStream);
		int arg10 = readHex2(inputStream);

		long result = arg1 + arg2 + arg3 + arg4 + arg5 + arg7 + arg8 + arg9 + arg10;

		ackCommand(outputStream, TEST_DEVICE_HEADER, COMMAND_HEAVY_TEST);
		// data
		appendHex6(outputStream, result);
	}
    else if (header == COMMAND_DEBUG_TEST) {
		ackCommand(outputStream, TEST_DEVICE_HEADER, COMMAND_DEBUG_TEST);
        appendString(getErrorOutputStreamLogger(), "TEST->DEBUG !");
    }
    /* TODO
    else if (header == COMMAND_NOTIFY_TEST) {
            int argument = readHex2(inputStream);
            argument *= 2;

            Buffer* buffer = getI2CSlaveOutputBuffer();
            OutputStream* i2cOutputStream = getOutputStream(buffer);

            // Add the value to I2C
            append(i2cOutputStream, COMMAND_NOTIFY_TEST);
            appendHex2(i2cOutputStream, argument);
        
            // Response to the call
            appendAck(outputStream);
            append(outputStream, COMMAND_NOTIFY_TEST);
            appendHex2(outputStream, argument);
    }
     */
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceTestInit,
    .deviceShutDown = &deviceTestShutDown,
    .deviceIsOk = &deviceTestIsOk,
    .deviceHandleRawData = &deviceTestHandleRawData
};

DeviceDescriptor* getTestDeviceDescriptor(void) {
    return &descriptor;
}

