#include <stdbool.h>

#include "serialDebugDevice.h"
#include "serialDebugDeviceInterface.h"

#include "../../common/i2c/i2cDebug.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/reader.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"
#include "../../common/log/logHandler.h"
#include "../../common/log/loggerDebug.h"

#include "../../common/serial/serialInputInterrupt.h"

#include "../../drivers/dispatcher/driverDataDispatcherList.h"
#include "../../drivers/dispatcher/driverDataDispatcherDebug.h"

#include "../../device/device.h"
#include "../../device/deviceConstants.h"
#include "../../device/deviceUsage.h"

void deviceSerialDebugInit(void) {
}

void deviceSerialDebugShutDown(void) {
}

bool deviceSerialDebugIsOk(void) {
    return true;
}

void deviceSerialDebugHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    // Serial Input Buffers
    if (header == COMMAND_SERIAL_INPUT_BUFFERS) {
        ackCommand(outputStream, SERIAL_DEBUG_DEVICE_HEADER, COMMAND_SERIAL_INPUT_BUFFERS);
        printSerialInputBuffers(getOutputStreamLogger(ALWAYS));         
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceSerialDebugInit,
    .deviceShutDown = &deviceSerialDebugShutDown,
    .deviceIsOk = &deviceSerialDebugIsOk,
    .deviceHandleRawData = &deviceSerialDebugHandleRawData,
};

DeviceDescriptor* getSerialDebugDeviceDescriptor(void) {
    return &descriptor;
}
