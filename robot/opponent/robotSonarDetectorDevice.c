#include "robotSonarDetectorDevice.h"
#include "robotSonarDetectorDeviceInterface.h"

#include "../../common/commons.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerList.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../device/device.h"

#include "../../drivers/sonar/srf02.h"

#include "../../device/motion/simple/motionDeviceInterface.h"

#include "../../robot/config/robotConfigDevice.h"
#include "../../robot/robot.h"

#include "../../main/motorboard/motorBoard.h"

#define SONAR_INDEX            0

/** Use or not the sonar. */
// static bool useSonar;

/** History of distances. */
static unsigned int distances[ROBOT_SONAR_DETECTOR_DEVICE_HISTORY_SIZE];

/** The index for history. */
static char distanceIndex;

/** The interrupt Counter. */
static char interruptCounter;

/** Value of the counter for which we do not check. */
static int doNotCheckBeforeCounter;

static bool obstacle;

static bool readNextDistanceFlag;

static char sonarStatus;

void setSonarStatus(unsigned char aSonarStatus) {
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

bool checkObstacle() {
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
        return true;
    }
    return false;
}

void deviceRobotSonarDetectorCallbackFunc(Timer* timer) {
    interruptCounter++;
    // return if we do not want
    if (interruptCounter <= doNotCheckBeforeCounter) {
        return;
    }
    doNotCheckBeforeCounter = 0;
    // rearm flags
    interruptCounter = 0;

    readNextDistanceFlag = true;
}

void readNextDistance() {
    if (!readNextDistanceFlag) {
        return;
    }
    readNextDistanceFlag = false;

    unsigned int distance = getSRF02DistanceEndRanging(SONAR_INDEX);
    delaymSec(1);
    startSRF02Ranging(SONAR_INDEX);
    distances[(unsigned int) distanceIndex] = distance;

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
        obstacle = true;
    }
}

bool notifyObstacle() {
    readNextDistance();
    if (!obstacle) {
        return false;
    }
    // we notify only one time
    obstacle = false;

    // We notify only if it's active
    if (sonarStatus) {
        stopRobotObstacle();
        return true;
    }

    return false;
}

void deviceRobotSonarDetectorInit() {
    // Timer for detector
    addTimer(ROBOT_SONAR_DETECTOR_TIMER_INDEX,
            TIME_DIVIDER_16_HERTZ,
            deviceRobotSonarDetectorCallbackFunc, "ROBOT SONAR DETECTOR TIMER");
    // useSonar = isConfigSet(CONFIG_USE_LASER_MASK);
    clearHistory();
    startSRF02Ranging(SONAR_INDEX);
    delaymSec(65);
    getSRF02DistanceEndRanging(SONAR_INDEX);
    obstacle = false;
    readNextDistanceFlag = false;
}

void deviceRobotSonarDetectorShutDown() {

}

bool deviceRobotSonarDetectorIsOk() {
    return true;
}

void deviceRobotSonarDetectorHandleRawData(char commandHeader,
        InputStream* inputStream,
        OutputStream* outputStream) {

    if (commandHeader == COMMAND_SET_SONAR_STATUS) {
        sonarStatus = readHex2(inputStream);
        ackCommand(outputStream, ROBOT_SONAR_DETECTOR_DEVICE_HEADER, COMMAND_SET_SONAR_STATUS);
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
