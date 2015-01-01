#include "motorDriver.h"

#include <stdbool.h>

#include "../../common/io/buffer.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logHandler.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"
#include "../../drivers/dispatcher/driverDataDispatcher.h"

bool motorDriverInit(void) {
    return true;
}

void motorDriverShutDown(void) {
}

bool motorDriverIsOk(void) {
    return true;
}

const char* motorDriverGetName(void) {
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
