#include <stdbool.h>
#include <stdlib.h>

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

static long demoCounter = 0;

void deviceTimerInit(void) {
}

void deviceTimerShutDown(void) {
} 

bool deviceTimerIsOk(void) {
    return true;
}

/**
 * The interrupt demo timer.
 */
void interruptDemoTimerCallbackFunc(Timer* timer) {
    appendStringAndDec(getOutputStreamLogger(ALWAYS), "counter=", demoCounter);
    appendCRLF(getOutputStreamLogger(ALWAYS));
    demoCounter++;
}

Timer* addTimerDemo(void) {
    Timer* result = addTimer(DEMO_TIMER_INDEX,
             TIME_DIVIDER_1_HERTZ,
             &interruptDemoTimerCallbackFunc,
             "DEMO");
    result->enabled = true;
    return result;
}

void deviceTimerHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream) {
    if (commandHeader == COMMAND_TIMER_LIST) {
        printTimerList(getOutputStreamLogger(ALWAYS), getTimerList());
        ackCommand(outputStream, TIMER_DEVICE_HEADER, COMMAND_TIMER_LIST);
    }    
    else if (commandHeader == COMMAND_TIMER_ENABLE_DEMO) {
        Timer* timer = getTimerByCode(DEMO_TIMER_INDEX);
        if (timer == NULL) {
            addTimerDemo();
        }
        ackCommand(outputStream, TIMER_DEVICE_HEADER, COMMAND_TIMER_ENABLE_DEMO);
    }
    else if (commandHeader == COMMAND_TIMER_DISABLE_DEMO) {
        Timer* timer = getTimerByCode(DEMO_TIMER_INDEX);
        if (timer != NULL) {
            timer->enabled = false;
        }
        ackCommand(outputStream, TIMER_DEVICE_HEADER, COMMAND_TIMER_DISABLE_DEMO);
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
