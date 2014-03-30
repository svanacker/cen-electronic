/**
  Small unit of code which detects the start of the match, by looping the
  state of a pin
  @author svanacker
  @version 17/04/2010
 */
#include "../../common/commons.h"

#ifdef PROG_32
	#include <p32xxxx.h>
#else
	#include <p30fxxxx.h>
#endif

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

void initStartMatchDetector() {

}

void stopStartMatchDetector() {

}

bool isStartMatchDetectorDeviceOk() {
    return true;
}

void loopUntilStart(handleFunctionType* handleFunction) {
	#ifndef PROG_32
    while (START_DETECTOR_PIN) {
        // Call back to be able to manage the robot while waiting for start.
        handleFunction();
    }
	#endif
}

char isStarted() {
	#ifndef PROG_32
    char readPin;
    readPin = START_DETECTOR_PIN;
    return readPin != 0;
	#endif
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

void deviceStartMatchDetectorHandleRawData(char header,
        InputStream* inputStream,
        OutputStream* outputStream) {
    if (header == COMMAND_STEP_BY_STEP) {
        appendAck(outputStream);
		robotNextStep();
        append(outputStream, COMMAND_STEP_BY_STEP);
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
