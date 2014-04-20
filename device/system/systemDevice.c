#include "systemDevice.h"
#include "systemDeviceInterface.h"

#include "../../common/delay/cenDelay.h"

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

bool deviceSystemIsOk() {
    return true;
}

void deviceSystemHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
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
