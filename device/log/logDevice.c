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

void deviceLogHandleRawData(unsigned char header, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    if (header == COMMAND_GET_LOG_COUNT) {
        ackCommand(outputStream, LOG_DEVICE_HEADER, COMMAND_GET_LOG_COUNT);
        unsigned logCount = getLogHandlerCount(getLoggerInstance()->logHandlerList);
        appendHex2(outputStream, logCount);
    }
    else if (header == COMMAND_WRITE_HANDLER_LOG_LEVEL) {
        // data
        ackCommand(outputStream, LOG_DEVICE_HEADER, COMMAND_WRITE_HANDLER_LOG_LEVEL);

        int logHandlerIndex = readHex2(inputStream);
        int logLevel = readHex2(inputStream);

        LogHandler* logHandler = getLogHandler(getLoggerInstance()->logHandlerList, logHandlerIndex);
        logHandler->logLevel = logLevel;
    }
    else if (header == COMMAND_WRITE_GLOBAL_LOG_LEVEL) {
        // data
        ackCommand(outputStream, LOG_DEVICE_HEADER, COMMAND_WRITE_GLOBAL_LOG_LEVEL);
        int logLevel = readHex2(inputStream);

        Logger* logger = getLoggerInstance();
        logger->globalLogLevel = logLevel;
    }
    else if (header == COMMAND_LOG_HANDLER_LIST) {
        ackCommand(outputStream, LOG_DEVICE_HEADER, COMMAND_LOG_HANDLER_LIST);
        printLogger(getInfoOutputStreamLogger());
    }
    else if (header == COMMAND_TEST_LOG) {
        ackCommand(outputStream, LOG_DEVICE_HEADER, COMMAND_TEST_LOG);
        int logLevel = readHex2(inputStream);
        // Get the outputStreamLogger with the right Level
        OutputStream* logOutputStream = getOutputStreamLogger(logLevel, getLoggerInstance()->defaultLogCategoryMask);
        appendString(logOutputStream, "LOG_TEST !");
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
