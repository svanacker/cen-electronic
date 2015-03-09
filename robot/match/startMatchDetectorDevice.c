#include <stdbool.h>
#include <stdlib.h>

#include "../../common/commons.h"

// #include <plib.h>

#include "startMatchDetector.h"
#include "startMatchDetectorDevice.h"
#include "startMatchDetectorDeviceInterface.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logLevel.h"
#include "../../common/log/logger.h"

#include "../../device/device.h"

#include "../../drivers/strategy/strategyDriver.h"


#include "../../robot/config/robotConfigDevice.h"

static StartMatchDetector* startMatchDetector;

void initStartMatchDetectorDevice(void) {

}

void stopStartMatchDetectorDevice(void) {

}

bool isStartMatchDetectorDeviceOk(void) {
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

void showWaitingStart(OutputStream* pcOutputStream) {
    appendString(pcOutputStream, MESSAGE_TO_PC_RESET);
    appendString(getAlwaysOutputStreamLogger(), "CFG:");
    appendStringConfig(getAlwaysOutputStreamLogger());
    println(getAlwaysOutputStreamLogger());
    appendString(getAlwaysOutputStreamLogger(), "Waiting start:");
}

void showStarted(OutputStream* pcOutputStream) {
    // Notify the pc that the match started
    appendString(pcOutputStream, MESSAGE_TO_PC_START);
    appendStringCRLF(getAlwaysOutputStreamLogger(), "Go !");
}

void deviceStartMatchDetectorHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream) {
    if (commandHeader == COMMAND_STEP_BY_STEP) {
        robotNextStep();
        ackCommand(outputStream, START_MATCH_DETECTOR_DEVICE_HEADER, COMMAND_STEP_BY_STEP);
    }
}

// Allocate memory
DeviceDescriptor startMatchDetectorDevice = {
    .deviceInit = &initStartMatchDetectorDevice,
    .deviceShutDown = &stopStartMatchDetectorDevice,
    .deviceIsOk = &isStartMatchDetectorDeviceOk,
    .deviceHandleRawData = &deviceStartMatchDetectorHandleRawData,
};

DeviceDescriptor* getStartMatchDetectorDeviceDescriptor(StartMatchDetector* startMatchDetectorParam) {
    startMatchDetector = startMatchDetectorParam;
    return &startMatchDetectorDevice;
}
