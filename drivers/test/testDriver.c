#include <stdlib.h>
#include <stdbool.h>

#include "testDriver.h"

#include "../../common/error/error.h"
#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../device/test/testDeviceInterface.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"

// TO REMOVE !
#include <Windows.h>

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

int randomInRange(int range_min, int range_max) {
    int result = (int) ((double)rand() / (RAND_MAX + 1) * (range_max - range_min)
        + range_min);
    return result;
}

bool testDriverIntensive(unsigned int testCount) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    InputStream* resultStream = getDriverResponseInputStream();
    srand((unsigned)time(NULL));

    unsigned int i;
    for (i = 0; i < testCount; i++) {
        append(outputStream, TEST_DEVICE_HEADER);
        append(outputStream, COMMAND_TEST);

        unsigned char value1 = (unsigned char)randomInRange(0, 255);
        unsigned char value2 = (unsigned char)randomInRange(0, 255);
        appendHex2(outputStream, value1);
        appendHex2(outputStream, value2);

        bool ok = transmitFromDriverRequestBuffer();
        if (ok) {
            int result = readHex2(resultStream);
            int expected = value1 + value2;
            if (expected >= 256) {
                expected -= 256;
            }
            if (result != expected) {
                writeError(DEVICE_TEST_INTENSIVE_CHECK_PROBLEM);
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
