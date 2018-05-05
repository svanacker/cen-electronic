#include <stdlib.h>

#include "endMatch.h"
#include "endMatchDebug.h"

#include "endMatchDetectorDevice.h"
#include "endMatchDetectorDeviceInterface.h"

#include "../../common/commons.h"
#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerList.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logLevel.h"
#include "../../common/log/logger.h"

#include "../../device/device.h"
#include "../../device/transmitMode.h"

#include "../../robot/config/robotConfig.h"
#include "../../robot/config/robotConfigDevice.h"

// Forward declaration
EndMatch* getEndMatchDetectorEndMatchObject(void);

// COMMON PART

void initEndMatchDetector(void) {
}

void stopEndMatchDetector(void) {

}

bool isEndMatchDetectorDeviceOk(void) {
    return true;
}

void deviceEndMatchDetectorHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    // DEBUG
    if (commandHeader == COMMAND_END_MATCH_DETECTOR_DEBUG) {
        ackCommand(outputStream, END_MATCH_DETECTOR_DEVICE_HEADER, COMMAND_END_MATCH_DETECTOR_DEBUG);
        EndMatch* endMatch = getEndMatchDetectorEndMatchObject();
        OutputStream* debugOutputStream = getDebugOutputStreamLogger();
        printEndOfMatchTable(debugOutputStream, endMatch);
    }
    else if (commandHeader == COMMAND_SHOW_MATCH_ENDED) {
        ackCommand(outputStream, END_MATCH_DETECTOR_DEVICE_HEADER, COMMAND_SHOW_MATCH_ENDED);
        EndMatch* endMatch = getEndMatchDetectorEndMatchObject();
        OutputStream* debugOutputStream = getAlwaysOutputStreamLogger();
        showEndAndScore(endMatch, debugOutputStream);
    }
    // Getter
    else if (commandHeader == COMMAND_GET_TIME_LEFT) {
        ackCommand(outputStream, END_MATCH_DETECTOR_DEVICE_HEADER, COMMAND_GET_TIME_LEFT);
        EndMatch* endMatch = getEndMatchDetectorEndMatchObject();
        appendHex2(outputStream, MATCH_DURATION - endMatch->currentTimeInSecond);
    }
    // Setters
    else if (commandHeader == COMMAND_SET_CURRENT_TIME_IN_SECOND) {
        ackCommand(outputStream, END_MATCH_DETECTOR_DEVICE_HEADER, COMMAND_SET_CURRENT_TIME_IN_SECOND);
        EndMatch* endMatch = getEndMatchDetectorEndMatchObject();
        unsigned char currentTimeInSecond = readHex2(inputStream);
        endMatch->currentTimeInSecond = currentTimeInSecond;
    }
    else if (commandHeader == COMMAND_SET_MATCH_DURATION) {
        ackCommand(outputStream, END_MATCH_DETECTOR_DEVICE_HEADER, COMMAND_SET_MATCH_DURATION);
        EndMatch* endMatch = getEndMatchDetectorEndMatchObject();
        unsigned char newMatchDuration = readHex2(inputStream);
        endMatch->matchDurationInSecond = newMatchDuration;
    }
}

static DeviceDescriptor endMatchDetectorDeviceDescriptor = {
    .deviceInit = &initEndMatchDetector,
    .deviceShutDown = &stopEndMatchDetector,
    .deviceIsOk = &isEndMatchDetectorDeviceOk,
    .deviceHandleRawData = &deviceEndMatchDetectorHandleRawData,
};

EndMatch* getEndMatchDetectorEndMatchObject(void) {
    return (EndMatch*)endMatchDetectorDeviceDescriptor.object;
}

DeviceDescriptor* getEndMatchDetectorDeviceDescriptor(EndMatch* endMatchParam) {
    endMatchDetectorDeviceDescriptor.object = (int*)endMatchParam;
    return &endMatchDetectorDeviceDescriptor;
}
