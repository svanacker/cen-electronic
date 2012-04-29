#include "robotSonarDetectorDevice.h"
#include "robotSonarDetectorDeviceInterface.h"

#include "../common/commons.h"

#include "../common/cmd/commonCommand.h"

#include "../common/delay/delay30F.h"

#include "../common/io/inputStream.h"
#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"
#include "../common/io/reader.h"
#include "../common/io/stream.h"

#include "../common/timer/cenTimer.h"
#include "../common/timer/timerList.h"

#include "../common/log/logger.h"
#include "../common/log/logLevel.h"

#include "../device/device.h"

#include "../drivers/sonar/srf02.h"

#include "../device/motion/simple/motionDeviceInterface.h"

#include "../robot/config/robotConfigDevice.h"
#include "../robot/robot.h"

#include "../main/motorBoard/motorBoard.h"

/** The timer struct to check the state of the sonar */
static Timer robotSonarDetectorDeviceTimer;

/** Use or not the sonar. */
// static BOOL useSonar;

/** History of distances. */
static unsigned int distances[ROBOT_SONAR_DETECTOR_DEVICE_HISTORY_SIZE];

/** The index for history. */
static int distanceIndex;

/** The interrupt Counter. */
static int interruptCounter;

/** Value of the counter for which we do not check. */
static int doNotCheckBeforeCounter;

static BOOL obstacle;

static BOOL readNextDistanceFlag;

static int sonarStatus;

void setSonarStatus(int aSonarStatus) {
	sonarStatus = aSonarStatus;
}

void clearHistory() {
    unsigned int i;
    for (i = 0; i < ROBOT_SONAR_DETECTOR_DEVICE_HISTORY_SIZE; i++) {
        distances[i] = 0;
    }
    distanceIndex = 0;
    interruptCounter = 0;
    doNotCheckBeforeCounter = 0;
}

BOOL checkObstacle() {
    unsigned int i;
    unsigned int matchCount = 0;
    for (i = 0; i < ROBOT_SONAR_DETECTOR_DEVICE_HISTORY_SIZE; i++) {
        if (distances[i] != 0 && distances[i] < ROBOT_SONAR_DETECTOR_DEVICE_DISTANCE_THRESHOLD) {
            matchCount++;
        }
    }
    if (matchCount >= ROBOT_SONAR_DETECTOR_DEVICE_HISTORY_THRESHOLD) {
        clearHistory();
        // Wait 30 interrupt before rearming test
        doNotCheckBeforeCounter = ROBOT_SONAR_DETECTOR_TIMER_SKIP_FOR_NEW_DETECTION;
        return TRUE;
    }
    return FALSE;
}

void deviceRobotSonarDetectorCallbackFunc(void) {
    interruptCounter++;
    // return if we do not want
    if (interruptCounter <= doNotCheckBeforeCounter) {
        return;
    }
    doNotCheckBeforeCounter = 0;
    // rearm flags
    interruptCounter = 0;

    readNextDistanceFlag = TRUE;
}

void readNextDistance() {
    if (!readNextDistanceFlag) {
        return;
    }
    readNextDistanceFlag = FALSE;

    unsigned int distance = getSRF02DistanceEndRanging();
    delaymSec(1);
    startSRF02Ranging();
    distances[distanceIndex] = distance;

    /*
    appendDec(getOutputStreamLogger(DEBUG), distance);
    append(getOutputStreamLogger(DEBUG), '.');
     */

    // Manage index of history
    distanceIndex++;
    if (distanceIndex > ROBOT_SONAR_DETECTOR_DEVICE_HISTORY_SIZE) {
        distanceIndex = 0;
    }

    if (checkObstacle()) {
        // for the main LOOP
        obstacle = TRUE;
    }
}

BOOL notifyObstacle() {
    readNextDistance();
    if (!obstacle) {
        return FALSE;
    }
    // we notify only one time
    obstacle = FALSE;

    // We notify only if it's active
    if (sonarStatus) {
        stopRobotObstacle();
        return TRUE;
    }

    return FALSE;
}

void deviceRobotSonarDetectorInit() {
    // Timer for detector
    initTimer(&robotSonarDetectorDeviceTimer,
            ROBOT_SONAR_DETECTOR_TIMER_INDEX,
            TIME_DIVISER_16_HERTZ,
            deviceRobotSonarDetectorCallbackFunc);
    // useSonar = isConfigSet(CONFIG_USE_LASER_MASK);
    clearHistory();
    startSRF02Ranging();
    delaymSec(65);
    getSRF02DistanceEndRanging();
    addTimer(&robotSonarDetectorDeviceTimer);
    obstacle = FALSE;
    readNextDistanceFlag = FALSE;
}

void deviceRobotSonarDetectorShutDown() {

}

BOOL deviceRobotSonarDetectorIsOk() {
    return TRUE;
}

void deviceRobotSonarDetectorHandleRawData(char header,
        InputStream* inputStream,
        OutputStream* outputStream) {

    if (header == COMMAND_SET_SONAR_STATUS) {
        sonarStatus = readHex2(inputStream);
        appendAck(outputStream);
        append(outputStream, COMMAND_SET_SONAR_STATUS);
    }
}


static DeviceDescriptor descriptor = {
    .deviceInit = &deviceRobotSonarDetectorInit,
    .deviceShutDown = &deviceRobotSonarDetectorShutDown,
    .deviceIsOk = &deviceRobotSonarDetectorIsOk,
    .deviceHandleRawData = &deviceRobotSonarDetectorHandleRawData,
};

DeviceDescriptor* getRobotSonarDetectorDeviceDescriptor() {
    return &descriptor;
}
