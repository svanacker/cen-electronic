#include <stdlib.h>
#include <stdbool.h>

#include "testDriver.h"

#include "../../common/error/error.h"
#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"

#include "../../common/math/random.h"

#include "../../device/test/testDeviceInterface.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"

signed int testDriverGetValue(signed int argument1, signed int argument2) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    InputStream* resultStream = getDriverResponseInputStream();
    append(outputStream, TEST_DEVICE_HEADER);
    append(outputStream, COMMAND_TEST);
    appendHex2(outputStream, argument1);
    appendHex2(outputStream, argument2);

    bool ok = transmitFromDriverRequestBuffer();
    if (ok) {
        int result = readHex2(resultStream);
        return result;
    }
    return 0;
}

bool testDriverIntensive(unsigned int testCount) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    InputStream* resultStream = getDriverResponseInputStream();
    

    unsigned int i;
    for (i = 0; i < testCount; i++) {
        append(outputStream, TEST_DEVICE_HEADER);
        append(outputStream, COMMAND_HEAVY_TEST);

        unsigned char value1 = (unsigned char)randomInRange(0, 255);
        unsigned char value2 = (unsigned char)randomInRange(0, 255);
		unsigned int value3 = (unsigned int) randomInRange(0, 32535);
		unsigned int value4 = (unsigned int) randomInRange(0, 32535);
		unsigned char value5 = randomInRange(0, 32535);
		// Separator / value 6
		unsigned char value7 = (unsigned char)randomInRange(0, 255);
		unsigned int value8 = (unsigned int)randomInRange(0, 32535);
		unsigned long value9 = (unsigned long)randomInRange(0, 32535);
		unsigned char value10 = (unsigned char)randomInRange(0, 255);
        appendHex2(outputStream, value1);
        appendHex2(outputStream, value2);
		appendHex4(outputStream, value3);
		appendHex4(outputStream, value4);
		appendHex2(outputStream, value5);
		appendSeparator(outputStream);
		appendHex2(outputStream, value7);
		appendHex4(outputStream, value8);
		appendHex6(outputStream, value9);
		appendHex2(outputStream, value10);

        bool ok = transmitFromDriverRequestBuffer();
        if (ok) {
            int actual = readHex6(resultStream);
            long expected = value1 + value2 + value3 + value4 + value5 + value7 + value8 + value9 + value10;
			if (actual != expected) {
                writeError(DEVICE_TEST_INTENSIVE_CHECK_PROBLEM);
				appendStringAndDec(getErrorOutputStreamLogger(), " : expected=", expected);
				appendStringAndDec(getErrorOutputStreamLogger(), ", actual=", actual);
				appendCRLF(getErrorOutputStreamLogger());
				return false;
            }
        }
        else {
            return false;
        }
    }
    return true;
}

// DRIVER INTERFACE

bool testDriverInit(void) {
    return true;
}

void testDriverShutDown(void) {
}

bool testDriverIsOk(void) {
    return true;
}

const char* testDriverGetName(void) {
    return "testDriver";
}

static DriverDescriptor descriptor = {
    &testDriverInit,
    &testDriverShutDown,
    &testDriverGetName,
};

DriverDescriptor* testDriverGetDescriptor() {
    return &descriptor;
}
