#include "systemDevice.h"
#include "systemDeviceInterface.h"

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

void deviceSystemInit() {
}

void deviceSystemShutDown() {
}

BOOL deviceSystemIsOk() {
    return TRUE;
}

void deviceSystemHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {

#ifdef DEVICE_ENABLE_CHANGE_LOG
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
#endif
	if (header == COMMAND_PING) {
        // data
        appendAck(outputStream);
        append(outputStream, COMMAND_PING);
    } else if (header == COMMAND_USAGE) {
        appendAck(outputStream);
        append(outputStream, COMMAND_USAGE);
        // we don't use driver stream (buffered->too small), instead of log (not buffered)
        printDeviceListUsage(getOutputStreamLogger(INFO));
    } else if (header == COMMAND_WAIT) {
        appendAck(outputStream);
        int mSec = readHex4(inputStream);
        delaymSec(mSec);
        append(outputStream, COMMAND_WAIT);
    } else if (header == COMMAND_PIC_NAME) {
        appendAck(outputStream);
        appendString(getOutputStreamLogger(ALWAYS), getPicName());
        append(outputStream, COMMAND_PIC_NAME);
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
    .deviceInit = &deviceSystemInit,
    .deviceShutDown = &deviceSystemShutDown,
    .deviceIsOk = &deviceSystemIsOk,
    .deviceHandleRawData = &deviceSystemHandleRawData,
};

DeviceDescriptor* getSystemDeviceDescriptor() {
    return &descriptor;
}
