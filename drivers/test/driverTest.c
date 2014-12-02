#include <stdlib.h>
#include <stdbool.h>

#include "driverTest.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../device/test/deviceTestInterface.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"

signed int driverTestGetValue(signed int argument1, signed int argument2) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    InputStream* resultStream = getDriverResponseInputStream();
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

bool driverTestInit() {
    return true;
}

void driverTestShutDown() {
}

bool driverTestIsOk() {
    return true;
}

const char* driverTestGetName() {
    return "driverTest";
}

static DriverDescriptor descriptor = {
    &driverTestInit,
    &driverTestShutDown,
    &driverTestGetName,
};

DriverDescriptor* driverTestGetDescriptor() {
    return &descriptor;
}
