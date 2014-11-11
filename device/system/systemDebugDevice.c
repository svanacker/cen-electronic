#include "systemDebugDevice.h"
#include "systemDebugDeviceInterface.h"

#include "../../common/i2c/i2cDebug.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/reader.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/stream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"
#include "../../common/log/logHandler.h"
#include "../../common/log/loggerDebug.h"

#include "../../common/serial/serialInputInterrupt.h"

#include "../../drivers/dispatcher/driverDataDispatcherList.h"
#include "../../drivers/dispatcher/driverDataDispatcherDebug.h"

#include "../../device/device.h"
#include "../../device/deviceUsage.h"

void deviceSystemDebugInit() {
}

void deviceSystemDebugShutDown() {
}

bool deviceSystemDebugIsOk() {
    return true;
}

void deviceSystemDebugHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    if (header == COMMAND_WRITE_LOG_LEVEL) {
        int logHandlerIndex = readHex2(inputStream);
        int logLevel = readHex2(inputStream);

        LogHandler* logHandler = getLogHandler(getLoggerInstance()->logHandlerList, logHandlerIndex);
        logHandler->logLevel = logLevel;

        // data
        ackCommand(outputStream, SYSTEM_DEBUG_DEVICE_HEADER, COMMAND_WRITE_LOG_LEVEL);
        // we don't use driver stream (buffered->too small), instead of log (not buffered)
        printLogger(getOutputStreamLogger(ALWAYS));
    }
    // Dispatcher List
    else if (header == COMMAND_DISPATCHER_LIST) {
        ackCommand(outputStream, SYSTEM_DEBUG_DEVICE_HEADER, COMMAND_DISPATCHER_LIST);
        DriverDataDispatcherList* dispatcherList = getDispatcherList();
        printDriverDataDispatcherList(getOutputStreamLogger(ALWAYS), dispatcherList);         
    }
    // Serial Input Buffers
    else if (header == COMMAND_SERIAL_INPUT_BUFFERS) {
        ackCommand(outputStream, SYSTEM_DEBUG_DEVICE_HEADER, COMMAND_SERIAL_INPUT_BUFFERS);
        printSerialInputBuffers(getOutputStreamLogger(ALWAYS));         
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceSystemDebugInit,
    .deviceShutDown = &deviceSystemDebugShutDown,
    .deviceIsOk = &deviceSystemDebugIsOk,
    .deviceHandleRawData = &deviceSystemDebugHandleRawData,
};

DeviceDescriptor* getSystemDebugDeviceDescriptor() {
    return &descriptor;
}
