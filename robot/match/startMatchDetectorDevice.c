/**
  Small unit of code which detects the start of the match, by looping the
  state of a pin
  @author svanacker
  @version 17/04/2010
 */
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
    appendString(getOutputStreamLogger(ALWAYS), "CFG:");
    appendStringConfig(getOutputStreamLogger(ALWAYS));
    println(getOutputStreamLogger(ALWAYS));
    appendString(getOutputStreamLogger(ALWAYS), "Waiting start:");
}

void showStarted(OutputStream* pcOutputStream) {
    // Notify the pc that the match started
    appendString(pcOutputStream, MESSAGE_TO_PC_START);
    appendStringCRLF(getOutputStreamLogger(ALWAYS), "Go !");
}

void deviceStartMatchDetectorHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    if (header == COMMAND_STEP_BY_STEP) {
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
