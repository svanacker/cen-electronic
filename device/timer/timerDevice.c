#include <stdbool.h>
#include <stdlib.h>

#include "timerDevice.h"
#include "timerDeviceInterface.h"

#include "../../common/delay/cenDelay.h"
#include "../../common/timer/delayTimer.h"
#include "../../common/timer/timerDebug.h"
#include "../../common/timer/timerConstants.h"
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
    appendStringAndDec(getInfoOutputStreamLogger(), "counter=", demoCounter);
    appendCRLF(getInfoOutputStreamLogger());
    demoCounter++;
}

Timer* addTimerDemo(void) {
    Timer* result = addTimer(DEMO_TIMER_CODE,
            TIME_DIVIDER_1_HERTZ,
            &interruptDemoTimerCallbackFunc,
            "DEMO",
            NULL);
    // addTimer could return null if not enough timer => In this case, it will change setErrorCode, and return NULL
    if (result != NULL) {
        result->enabled = true;
    }
    return result;
}

void deviceTimerHandleRawData(unsigned char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    if (commandHeader == COMMAND_TIMER_LIST) {
        printTimerList(getInfoOutputStreamLogger(), getTimerList());
        ackCommand(outputStream, TIMER_DEVICE_HEADER, COMMAND_TIMER_LIST);
    } else if (commandHeader == COMMAND_TIMER_COUNT) {
        ackCommand(outputStream, TIMER_DEVICE_HEADER, COMMAND_TIMER_COUNT);
        unsigned timerCount = getTimerCount();
        appendHex2(outputStream, timerCount);
    } else if (commandHeader == COMMAND_TIMER_READ) {
        ackCommand(outputStream, TIMER_DEVICE_HEADER, COMMAND_TIMER_READ);
        unsigned char timerIndex = readHex2(inputStream);
        Timer* timer = getTimerByIndex(timerIndex);
        appendHex2(outputStream, timerIndex);
        appendSeparator(outputStream);
        appendHex2(outputStream, timer->timerCode);
        appendSeparator(outputStream);
        appendHex4(outputStream, timer->timeDiviser);
        appendSeparator(outputStream);
        appendHex4(outputStream, timer->timeInternalCounter);
        appendSeparator(outputStream);
        appendHex6(outputStream, timer->time);
        appendSeparator(outputStream);
        appendHex6(outputStream, timer->markTime);
        appendSeparator(outputStream);
        appendBool(outputStream, timer->enabled);
    }// Enable / Tisable
    else if (commandHeader == COMMAND_TIMER_ENABLE_DISABLE) {
        unsigned char timerIndex = readHex2(inputStream);
        Timer* timer = getTimerByIndex(timerIndex);

        checkIsSeparator(inputStream);

        unsigned enableAsChar = readHex(inputStream);
        bool enabled = enableAsChar != 0;
        timer->enabled = enabled;
        ackCommand(outputStream, TIMER_DEVICE_HEADER, COMMAND_TIMER_ENABLE_DISABLE);
    }// Mark
    else if (commandHeader == COMMAND_TIMER_MARK) {
        unsigned char timerIndex = readHex2(inputStream);
        Timer* timer = getTimerByIndex(timerIndex);
        unsigned long time = markTimer(timer);
        ackCommand(outputStream, TIMER_DEVICE_HEADER, COMMAND_TIMER_MARK);
        appendHex6(outputStream, time);
    } else if (commandHeader == COMMAND_TIMER_TIME_SINCE_LAST_MARK) {
        unsigned char timerIndex = readHex2(inputStream);
        Timer* timer = getTimerByIndex(timerIndex);
        unsigned long value = getTimeSinceLastMark(timer);
        ackCommand(outputStream, TIMER_DEVICE_HEADER, COMMAND_TIMER_TIME_SINCE_LAST_MARK);
        appendHex6(outputStream, value);
    } else if (commandHeader == COMMAND_TIMER_TIMEOUT) {
        unsigned char timerIndex = readHex2(inputStream);
        checkIsSeparator(inputStream);
        unsigned long timeToCheck = (unsigned long) readHex6(inputStream);
        Timer* timer = getTimerByIndex(timerIndex);
        bool value = timeout(timer, timeToCheck);
        ackCommand(outputStream, TIMER_DEVICE_HEADER, COMMAND_TIMER_TIMEOUT);
        appendHex2(outputStream, timerIndex);
        appendSeparator(outputStream);
        appendBool(outputStream, value);
    }// Demo
    else if (commandHeader == COMMAND_TIMER_DEMO) {
        Timer* timer = getTimerByCode(DEMO_TIMER_CODE);
        if (timer == NULL) {
            timer = addTimerDemo();
        }
        // Timer could be null when adding the timerDemo because of limit, we don't want any crash !
        if (timer != NULL) {
            unsigned enableAsChar = readHex(inputStream);
            bool enabled = enableAsChar != 0;
            timer->enabled = enabled;
        }
        ackCommand(outputStream, TIMER_DEVICE_HEADER, COMMAND_TIMER_DEMO);
    } else if (commandHeader == COMMAND_TIMER_DELAY_WAIT) {
        ackCommand(outputStream, TIMER_DEVICE_HEADER, COMMAND_TIMER_DELAY_WAIT);
        unsigned int milliSeconds = readHex4(inputStream);
        timerDelayMilliSeconds(milliSeconds);
    }
}

static DeviceDescriptor descriptor;

DeviceDescriptor* getTimerDeviceDescriptor(void) {
    initDeviceDescriptor(&descriptor,
            &deviceTimerInit,
            &deviceTimerShutDown,
            &deviceTimerIsOk,
            &deviceTimerHandleRawData,
            NULL);

    return &descriptor;
}

