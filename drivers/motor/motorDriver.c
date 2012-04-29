#include "motorDriver.h"

#include "../../common/commons.h"

#include "../../common/io/buffer.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logHandler.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"
#include "../../drivers/dispatcher/driverDataDispatcher.h"

BOOL motorDriverInit() {
    return TRUE;
}

void motorDriverShutDown() {
}

BOOL motorDriverIsOk() {
    return TRUE;
}

unsigned int motorDriverGetSoftwareRevision() {
    return 1;
}

const char* motorDriverGetName() {
    return "motorDriver";
}

BOOL motorDriverSendRawData(const char *data) {
    return FALSE;
}

static DriverDescriptor descriptor = {
    .driverEnabled = TRUE,
    .driverInit = &motorDriverInit,
    .driverShutDown = &motorDriverShutDown,
    .driverIsOk = &motorDriverIsOk,
    .driverGetSoftwareRevision = &motorDriverGetSoftwareRevision,
    .driverGetName = &motorDriverGetName
};

const DriverDescriptor* driverMotorGetDescriptor() {
    return &descriptor;
}

