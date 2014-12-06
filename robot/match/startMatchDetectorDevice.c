/**
  Small unit of code which detects the start of the match, by looping the
  state of a pin
  @author svanacker
  @version 17/04/2010
 */
#include <stdbool.h>

#include "../../common/commons.h"

// #include <plib.h>

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

void initStartMatchDetector(void) {

}

void stopStartMatchDetector(void) {

}

bool isStartMatchDetectorDeviceOk(void) {
    return true;
}

void loopUntilStart(handleFunctionType* handleFunction) {
    #ifndef PROG_32
    // TODO 
    /*
    while (START_DETECTOR_PIN) {
        // Call back to be able to manage the robot while waiting for start.
        handleFunction();
    }
    */
    #endif
}

bool isStarted(void) {
    return true;
    /*
    #ifndef PROG_32
    char readPin;
    // TODO !!!!
    //readPin = START_DETECTOR_PIN;
    return readPin != 0;
    #endif
    */
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
    .deviceInit = &initStartMatchDetector,
    .deviceShutDown = &stopStartMatchDetector,
    .deviceIsOk = &isStartMatchDetectorDeviceOk,
    .deviceHandleRawData = &deviceStartMatchDetectorHandleRawData,
};

DeviceDescriptor* getStartMatchDetectorDeviceDescriptor() {
    return &startMatchDetectorDevice;
}
