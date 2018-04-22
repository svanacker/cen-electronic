#include <stdlib.h>

#include "endMatch.h"

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

/** The struct to detect the end of the match. */
static EndMatch* endMatch;

// COMMON PART

void initEndMatchDetector(void) {
}

void stopEndMatchDetector(void) {

}

bool isEndMatchDetectorDeviceOk(void) {
    return true;
}

void deviceEndMatchDetectorHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    if (commandHeader == COMMAND_GET_TIME_LEFT) {
        ackCommand(outputStream, END_MATCH_DETECTOR_DEVICE_HEADER, COMMAND_GET_TIME_LEFT);
        appendHex2(outputStream, MATCH_DURATION - endMatch->currentTimeInSecond);
    }
}

static DeviceDescriptor endMatchDetectorDevice = {
    .deviceInit = &initEndMatchDetector,
    .deviceShutDown = &stopEndMatchDetector,
    .deviceIsOk = &isEndMatchDetectorDeviceOk,
    .deviceHandleRawData = &deviceEndMatchDetectorHandleRawData,
};

DeviceDescriptor* getEndMatchDetectorDeviceDescriptor(EndMatch* endMatchParam) {
    endMatch = endMatchParam;
    return &endMatchDetectorDevice;
}
