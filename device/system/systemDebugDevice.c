#include "systemDebugDevice.h"
#include "systemDebugDeviceInterface.h"

#include "../../common/delay/delay30F.h"

#include "../../common/i2c/i2cDebug.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/reader.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/stream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"
#include "../../common/log/logHandler.h"

#include "../../device/device.h"
#include "../../device/deviceUsage.h"

void deviceSystemDebugInit() {
}

void deviceSystemDebugShutDown() {
}

bool deviceSystemDebugIsOk() {
    return TRUE;
}

void deviceSystemDebugHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    if (header == COMMAND_LOG) {
        int logHandlerIndex = readHex2(inputStream);
        int logLevel = readHex2(inputStream);

        LogHandler* logHandler = getLogHandler(getLoggerInstance()->logHandlerList, logHandlerIndex);
        logHandler->logLevel = logLevel;

        // data
        appendAck(outputStream);
        append(outputStream, COMMAND_LOG);
        // we don't use driver stream (buffered->too small), instead of log (not buffered)
        printLogger(getOutputStreamLogger(ALWAYS));
    }
	// I2C Management
	else if (header == COMMAND_DEBUG_I2C) {
        appendAck(outputStream);
        printI2cDebugBuffers();

        // Response
        append(outputStream, COMMAND_DEBUG_I2C);
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
