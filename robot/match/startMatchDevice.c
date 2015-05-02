#include <stdbool.h>
#include <stdlib.h>

#include "../../common/commons.h"

// #include <plib.h>

#include "startMatchDetector.h"
#include "startMatchDevice.h"
#include "startMatchDeviceInterface.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/eeprom/eeprom.h"
#include "../../common/eeprom/eepromAreas.h"

#include "../../common/log/logLevel.h"
#include "../../common/log/logger.h"

#include "../../device/device.h"

#include "../../drivers/strategy/strategyDriver.h"


#include "../../robot/config/robotConfigDevice.h"

static StartMatchDetector* startMatchDetector;
static Eeprom* startMatchEeprom;

#define EEPROM_START_MATCH_ROBOT_POSITION_X_OFFSET         0
#define EEPROM_START_MATCH_ROBOT_POSITION_Y_OFFSET         6
#define EEPROM_START_MATCH_ROBOT_POSITION_ANGLE_OFFSET    12

#define EEPROM_START_MATCH_ROBOT_POSITION_BLOCK_SIZE      20

void initStartMatchDevice(void) {

}

void stopStartMatchDevice(void) {

}

bool isStartMatchDeviceOk(void) {
    return true;
}

void loopUntilStart(handleFunctionType* handleFunction) {
    if (startMatchDetector == NULL) {
        return;
    }
    while (startMatchDetector->isMatchStartedFunction(startMatchDetector)) {
        handleFunction();
    }
}

bool isStarted(void) {
    if (startMatchDetector == NULL) {
        return false;
    }
    bool result = startMatchDetector->isMatchStartedFunction(startMatchDetector);
    return result;
}

void notifyWaitingStart(OutputStream* pcOutputStream) {
    appendString(pcOutputStream, NOTIFY_TO_PC_RESET);
    appendString(getAlwaysOutputStreamLogger(), "CFG:");
    appendStringConfig(getAlwaysOutputStreamLogger());
    println(getAlwaysOutputStreamLogger());
    appendString(getAlwaysOutputStreamLogger(), "Waiting start:");
}

void notifyStarted(OutputStream* pcOutputStream) {
    // Notify the pc that the match started
    appendString(pcOutputStream, NOTIFY_TO_PC_START);
    appendStringCRLF(getAlwaysOutputStreamLogger(), "Go !");
}

int getStartMatchDetectorEepromGetOffset(int color) {
    int result = EEPROM_START_MATCH_START_INDEX + color * EEPROM_START_MATCH_ROBOT_POSITION_BLOCK_SIZE;
    return result;
}

void deviceStartMatchDetectorHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream) {
    if (commandHeader == COMMAND_STEP_BY_STEP) {
        robotNextStep();
        ackCommand(outputStream, START_MATCH_DEVICE_HEADER, COMMAND_STEP_BY_STEP);
    }
    else if (commandHeader == COMMAND_START_MATCH_GET_INITIAL_POSITION) {
        ackCommand(outputStream, START_MATCH_DEVICE_HEADER, COMMAND_START_MATCH_GET_INITIAL_POSITION);
        int color = readHex2(inputStream);

        int globalOffset = getStartMatchDetectorEepromGetOffset(color);
        int x = eepromReadInt(startMatchEeprom, globalOffset + EEPROM_START_MATCH_ROBOT_POSITION_X_OFFSET);
        int y = eepromReadInt(startMatchEeprom, globalOffset + EEPROM_START_MATCH_ROBOT_POSITION_Y_OFFSET);
        int angle = eepromReadInt(startMatchEeprom, globalOffset + EEPROM_START_MATCH_ROBOT_POSITION_ANGLE_OFFSET);
        appendHex2(outputStream, color);
        appendSeparator(outputStream);
        appendHex4(outputStream, x);
        appendSeparator(outputStream);
        appendHex4(outputStream, y);
        appendSeparator(outputStream);
        appendHex4(outputStream, angle);
    }
    else if (commandHeader == COMMAND_START_MATCH_SET_INITIAL_POSITION) {
        ackCommand(outputStream, START_MATCH_DEVICE_HEADER, COMMAND_START_MATCH_SET_INITIAL_POSITION);

        int color = readHex2(inputStream);
        int globalOffset = getStartMatchDetectorEepromGetOffset(color);

        checkIsSeparator(inputStream);
        int x = readHex4(inputStream);

        checkIsSeparator(inputStream);
        int y = readHex4(inputStream);

        checkIsSeparator(inputStream);
        int angleDeciDeg = readHex4(inputStream);

        eepromWriteInt(startMatchEeprom, globalOffset + EEPROM_START_MATCH_ROBOT_POSITION_X_OFFSET, x);
        eepromWriteInt(startMatchEeprom, globalOffset + EEPROM_START_MATCH_ROBOT_POSITION_Y_OFFSET, y);
        eepromWriteInt(startMatchEeprom, globalOffset + EEPROM_START_MATCH_ROBOT_POSITION_ANGLE_OFFSET, angleDeciDeg);
    }
}

// Allocate memory
DeviceDescriptor startMatchDetectorDevice = {
    .deviceInit = &initStartMatchDevice,
    .deviceShutDown = &stopStartMatchDevice,
    .deviceIsOk = &isStartMatchDeviceOk,
    .deviceHandleRawData = &deviceStartMatchDetectorHandleRawData,
};

DeviceDescriptor* getStartMatchDeviceDescriptor(StartMatchDetector* startMatchDetectorParam, Eeprom* eeprom) {
    startMatchDetector = startMatchDetectorParam;
    startMatchEeprom = eeprom;
    return &startMatchDetectorDevice;
}
