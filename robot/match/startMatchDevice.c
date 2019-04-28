#include <stdbool.h>
#include <stdlib.h>

#include "../../common/commons.h"
#include "../../common/2d/2d.h"

#include "startMatch.h"
#include "startMatchDebug.h"
#include "startMatchDevice.h"
#include "startMatchDeviceInterface.h"
#include "endMatchDetectorDevice.h"

#include "../../common/io/binaryPrintWriter.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/eeprom/eeprom.h"
#include "../../common/eeprom/eepromAreas.h"

#include "../../common/log/logLevel.h"
#include "../../common/log/logger.h"

#include "../../device/device.h"

#include "../../robot/config/robotConfigDevice.h"

// Forward declaration
StartMatch* getStartMatchDetectorStartMatchObject(void);

void initStartMatchDevice(void) {

}

void stopStartMatchDevice(void) {

}

bool isStartMatchDeviceOk(void) {
    return true;
}

void notifyWaitingStart(StartMatch* startMatch, OutputStream* pcOutputStream) {
    appendString(pcOutputStream, NOTIFY_TO_PC_RESET);
    appendString(getAlwaysOutputStreamLogger(), "CFG:");
    appendBinary16(getAlwaysOutputStreamLogger(), getConfigValue(startMatch->robotConfig), 4);
    println(getAlwaysOutputStreamLogger());
    appendString(getAlwaysOutputStreamLogger(), "Waiting start:");
}

void notifyStarted(StartMatch* startMatch, OutputStream* pcOutputStream) {
    // Notify the pc that the match started
    appendString(pcOutputStream, NOTIFY_TO_PC_START);
    appendStringCRLF(getAlwaysOutputStreamLogger(), "Go !");
}

void deviceStartMatchDetectorHandleRawData(unsigned char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    if (commandHeader == COMMAND_MATCH_IS_STARTED) {
        StartMatch* startMatch = getStartMatchDetectorStartMatchObject();
        int value = isMatchStarted(startMatch);
        ackCommand(outputStream, START_MATCH_DEVICE_HEADER, COMMAND_MATCH_IS_STARTED);
        appendHex2(outputStream, value);
    }
    else if (commandHeader == COMMAND_START_MATCH_DEBUG) {
        StartMatch* startMatch = getStartMatchDetectorStartMatchObject();
        ackCommand(outputStream, START_MATCH_DEVICE_HEADER, COMMAND_START_MATCH_DEBUG);
        OutputStream* debugOutputStream = getDebugOutputStreamLogger();
        printStartMatchTable(debugOutputStream, startMatch);
    }
}

DeviceDescriptor startMatchDetectorDevice = {
    .deviceInit = &initStartMatchDevice,
    .deviceShutDown = &stopStartMatchDevice,
    .deviceIsOk = &isStartMatchDeviceOk,
    .deviceHandleRawData = &deviceStartMatchDetectorHandleRawData,
};

StartMatch* getStartMatchDetectorStartMatchObject(void) {
    return (StartMatch*)startMatchDetectorDevice.object;
}

DeviceDescriptor* getStartMatchDeviceDescriptor(StartMatch* startMatchParam) {
    startMatchDetectorDevice.object = (int*) startMatchParam;
    return &startMatchDetectorDevice;
}
