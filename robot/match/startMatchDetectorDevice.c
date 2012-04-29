/**
  Small unit of code which detects the start of the match, by looping the
  state of a pin
  @author svanacker
  @version 17/04/2010
 */
#include <p30fxxxx.h>
#include <libpic30.h>

#include "startMatchDetectorDevice.h"
#include "startMatchDetectorDeviceInterface.h"

#include "../../common/commons.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logLevel.h"
#include "../../common/log/logger.h"

#include "../../device/device.h"
#include "../../robot/config/robotConfigDevice.h"

void initStartMatchDetector() {

}

void stopStartMatchDetector() {

}

unsigned int isStartMatchDetectorDeviceOk() {
    return TRUE;
}

void loopUntilStart(handleFunctionType* handleFunction) {
    while (START_DETECTOR_PIN) {
        // Call back to be able to manage the robot while waiting for start.
        handleFunction();
    }
}

char isStarted() {
    char readPin;
    readPin = START_DETECTOR_PIN;
    return readPin != 0;
}

void showWaitingStart(OutputStream* pcOutputStream) {
    appendString(pcOutputStream, MESSAGE_TO_PC_RESET);
    appendString(getOutputStreamLogger(ALWAYS), "CFG:");
    appendStringCRLF(getOutputStreamLogger(ALWAYS), getStringConfig());
    appendString(getOutputStreamLogger(ALWAYS), "Waiting start:");
}

void showStarted(OutputStream* pcOutputStream) {
    // Notify the pc that the match started
    appendString(pcOutputStream, MESSAGE_TO_PC_START);
    appendStringCRLF(getOutputStreamLogger(ALWAYS), "Go !");
}

void deviceStartMatchDetectorHandleRawData(char header,
        InputStream* inputStream,
        OutputStream* outputStream) {
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
