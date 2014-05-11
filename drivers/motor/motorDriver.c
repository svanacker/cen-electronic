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

bool motorDriverInit() {
    return true;
}

void motorDriverShutDown() {
}

bool motorDriverIsOk() {
    return true;
}

const char* motorDriverGetName() {
    return "motorDriver";
}

bool motorDriverSendRawData(const char *data) {
    return false;
}

static DriverDescriptor descriptor = {
    .driverInit = &motorDriverInit,
    .driverShutDown = &motorDriverShutDown,
    .driverGetName = &motorDriverGetName
};

const DriverDescriptor* driverMotorGetDescriptor() {
    return &descriptor;
}

