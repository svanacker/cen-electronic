#include <stdbool.h>

#include "logDevice.h"
#include "logDeviceInterface.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/reader.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/loggerDebug.h"
#include "../../common/log/logLevel.h"
#include "../../common/log/logHandler.h"

#include "../../device/device.h"
#include "../../device/deviceDebug.h"
#include "../../device/deviceUsage.h"

void deviceLogInit(void) {
}

void deviceLogShutDown(void) {
} 

bool deviceLogIsOk(void) {
    return true;
}

void deviceLogHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    if (header == COMMAND_WRITE_LOG_LEVEL) {
        int logHandlerIndex = readHex2(inputStream);
        int logLevel = readHex2(inputStream);

        LogHandler* logHandler = getLogHandler(getLoggerInstance()->logHandlerList, logHandlerIndex);
        logHandler->logLevel = logLevel;

        // data
        ackCommand(outputStream, SYSTEM_DEBUG_DEVICE_HEADER, COMMAND_WRITE_LOG_LEVEL);
        // we don't use driver stream (buffered->too small), instead of log (not buffered)
        printLogger(getAlwaysOutputStreamLogger());
    }
    else if (header == COMMAND_LOG) {
        printLogger(getAlwaysOutputStreamLogger());
        ackCommand(outputStream, SYSTEM_DEVICE_HEADER, COMMAND_LOG);
    }    
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceLogInit,
    .deviceShutDown = &deviceLogShutDown,
    .deviceIsOk = &deviceLogIsOk,
    .deviceHandleRawData = &deviceLogHandleRawData,
};

DeviceDescriptor* getLogDeviceDescriptor(void) {
    return &descriptor;
}
