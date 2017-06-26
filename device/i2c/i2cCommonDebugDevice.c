#include <stdbool.h>
#include <stdlib.h>

#include "i2cCommonDebugDevice.h"
#include "i2cCommonDebugDeviceInterface.h"

#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/i2cDebug.h"
#include "../../common/i2c/i2cBusList.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/reader.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"
#include "../../common/log/logHandler.h"
#include "../../common/log/loggerDebug.h"

#include "../../device/device.h"
#include "../../device/deviceUsage.h"

void deviceI2cCommonDebugInit(void) {
}

void deviceI2cCommonDebugShutDown(void) {
}

bool deviceI2cCommonDebugIsOk(void) {
    return true;
}

void deviceI2cCommonDebugHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    // I2C Management
    if (header == COMMAND_I2C_DEBUG_COMMON_LIST_BUS) {
        ackCommand(outputStream, I2C_COMMON_DEBUG_DEVICE_HEADER, COMMAND_I2C_DEBUG_COMMON_LIST_BUS);
		printI2cBusList(getAlwaysOutputStreamLogger());
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceI2cCommonDebugInit,
    .deviceShutDown = &deviceI2cCommonDebugShutDown,
    .deviceIsOk = &deviceI2cCommonDebugIsOk,
    .deviceHandleRawData = &deviceI2cCommonDebugHandleRawData,
};

DeviceDescriptor* getI2cCommonDebugDeviceDescriptor() {
    return &descriptor;
}
