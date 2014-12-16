#include "systemDevice.h"
#include "systemDeviceInterface.h"

#include "../../common/delay/cenDelay.h"
#include "../../common/timer/timerDebug.h"
#include "../../common/timer/timerList.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/reader.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/stream.h"

#include "../../common/log/logger.h"
#include "../../common/log/loggerDebug.h"
#include "../../common/log/logLevel.h"
#include "../../common/log/logHandler.h"

#include "../../device/device.h"
#include "../../device/deviceUsage.h"

void deviceSystemInit(void) {
}

void deviceSystemShutDown(void) {
} 

bool deviceSystemIsOk(void) {
    return true;
}

void deviceSystemHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    if (header == COMMAND_PING) {
        // data
        ackCommand(outputStream, SYSTEM_DEVICE_HEADER, COMMAND_PING);
    }
    else if (header == COMMAND_DEVICE_LIST) {
        ackCommand(outputStream, SYSTEM_DEVICE_HEADER, COMMAND_DEVICE_LIST);
        printDeviceList(getOutputStreamLogger(INFO));
    } else if (header == COMMAND_USAGE) {
        ackCommand(outputStream, SYSTEM_DEVICE_HEADER, COMMAND_USAGE);
        // we don't use driver stream (buffered->too small), instead of log (not buffered)
        printDeviceList(getOutputStreamLogger(INFO));
    } else if (header == COMMAND_WAIT) {
        appendAck(outputStream);
        int mSec = readHex4(inputStream);
        delaymSec(mSec);
        append(outputStream, SYSTEM_DEVICE_HEADER);
        append(outputStream, COMMAND_WAIT);
    } else if (header == COMMAND_PIC_NAME) {
        appendString(getOutputStreamLogger(ALWAYS), getPicName());
        println(getOutputStreamLogger(ALWAYS));
        ackCommand(outputStream, SYSTEM_DEVICE_HEADER, COMMAND_PIC_NAME);
    } else if (header == COMMAND_LOG) {
        printLogger(getOutputStreamLogger(ALWAYS));
        ackCommand(outputStream, SYSTEM_DEVICE_HEADER, COMMAND_LOG);
    } else if (header == COMMAND_TIMER_LIST) {
        printTimerList(getOutputStreamLogger(ALWAYS), getTimerList());
        ackCommand(outputStream, SYSTEM_DEVICE_HEADER, COMMAND_TIMER_LIST);
    }	
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceSystemInit,
    .deviceShutDown = &deviceSystemShutDown,
    .deviceIsOk = &deviceSystemIsOk,
    .deviceHandleRawData = &deviceSystemHandleRawData,
};

DeviceDescriptor* getSystemDeviceDescriptor(void) {
    return &descriptor;
}
