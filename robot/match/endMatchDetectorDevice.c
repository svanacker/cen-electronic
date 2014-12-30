#include "endMatchDetectorDevice.h"
#include "endMatchDetectorDeviceInterface.h"

#include "../../common/commons.h"
#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerList.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logLevel.h"
#include "../../common/log/logger.h"

#include "../../device/device.h"
#include "../../device/transmitMode.h"

#include "../../robot/config/robotConfig.h"
#include "../../robot/config/robotConfigDevice.h"

#include "../../robot/2012/armDriver2012.h"

static bool matchStarted = false;

/** Current Time In Second. */
static int currentTimeInSecond = 0;

/** Flag to know if the robot must stop at the end of the match. */
static bool doNotEnd = false;

/** The timer struct to detect the end of the match. */
static Timer* endMatchDetectorDeviceTimer;

// SPECIFIC PART

void endMatchDetectorCallbackFunc(Timer* timer) {
    if (matchStarted) {
        currentTimeInSecond++;
    }
}

/**
* As there is a problem during init to load the config.
* We send it after
*/
void initEndMatchConfig(void) {
    doNotEnd = isConfigSet(CONFIG_DO_NOT_END);
}

void markStartMatch() {
    initEndMatchConfig();
    matchStarted = true;
    currentTimeInSecond = 0;
}

void showEnd(OutputStream* outputStream) {
    appendString(outputStream, "End of match");
}

int getCurrentTimeInSecond(void) {
    return currentTimeInSecond;
}

bool isEnd() {
    if (doNotEnd) {
        return false;
    }
    if (!matchStarted) {
        appendString(getOutputStreamLogger(LOG_LEVEL_ERROR), "You must call startMatch before");
    }
    bool result = currentTimeInSecond >= MATCH_DURATION;
    
    if (result) {    
        // If END
        armDriver2012Up(0);
    }
    return result;
}

// COMMON PART

void initEndMatchDetector(void) {
    endMatchDetectorDeviceTimer = addTimer(END_MATCH_DETECTOR_TIMER_CODE,
                                            TIME_DIVISER_1_HERTZ,
                                            endMatchDetectorCallbackFunc,
                                            "END MATCH TIMER");
}

void stopEndMatchDetector(void) {

}

bool isEndMatchDetectorDeviceOk(void) {
    return true;
}

void deviceEndMatchDetectorHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream) {
}

// allocate memory
static DeviceDescriptor endMatchDetectorDevice = {
    .deviceInit = &initEndMatchDetector,
    .deviceShutDown = &stopEndMatchDetector,
    .deviceIsOk = &isEndMatchDetectorDeviceOk,
    .deviceHandleRawData = &deviceEndMatchDetectorHandleRawData,
};

DeviceDescriptor* getEndMatchDetectorDeviceDescriptor() {
    return &endMatchDetectorDevice;
}
