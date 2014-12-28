#include "timerDevice.h"
#include "timerDeviceInterface.h"

#include "../../common/delay/cenDelay.h"
#include "../../common/timer/timerDebug.h"
#include "../../common/timer/timerList.h"

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

void deviceTimerInit(void) {
}

void deviceTimerShutDown(void) {
} 

bool deviceTimerIsOk(void) {
    return true;
}

void deviceTimerHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    if (header == COMMAND_TIMER_LIST) {
        printTimerList(getOutputStreamLogger(ALWAYS), getTimerList());
        ackCommand(outputStream, SYSTEM_DEVICE_HEADER, COMMAND_TIMER_LIST);
    }	
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceTimerInit,
    .deviceShutDown = &deviceTimerShutDown,
    .deviceIsOk = &deviceTimerIsOk,
    .deviceHandleRawData = &deviceTimerHandleRawData,
};

DeviceDescriptor* getTimerDeviceDescriptor(void) {
    return &descriptor;
}
