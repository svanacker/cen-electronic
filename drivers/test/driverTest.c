#include <stdlib.h>
#include "driverTest.h"

#include "../../common/io/buffer.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logHandler.h"

#include "../../device/deviceList.h"
#include "../../device/test/deviceTestInterface.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"

unsigned int driverTestGetValue(int argument) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    InputStream* resultStream = getDriverResponseInputStream();
    append(outputStream, COMMAND_TEST);
    appendHex2(outputStream, argument);

    bool ok = transmitFromDriverRequestBuffer();
    if (ok) {
        int result = readHex2(resultStream);
        return result;
    }
    return 0;
}

// DRIVER INTERFACE

bool driverTestInit() {
    return TRUE;
}

void driverTestShutDown() {
}

bool driverTestIsOk() {
    return TRUE;
}

unsigned int driverTestGetSoftwareRevision() {
    return 1;
}

const char* driverTestGetName() {
    return "driverTest";
}

static DriverDescriptor descriptor = {
//    TRUE,
    &driverTestInit,
    &driverTestShutDown,
//    &driverTestIsOk,
//    &driverTestGetSoftwareRevision,
    &driverTestGetName,
};

DriverDescriptor* driverTestGetDescriptor() {
    return &descriptor;
}
