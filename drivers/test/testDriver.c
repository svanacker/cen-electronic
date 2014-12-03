#include <stdlib.h>
#include <stdbool.h>

#include "testDriver.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

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
