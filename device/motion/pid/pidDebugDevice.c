#include <stdbool.h>

#include "pidDebugDevice.h"
#include "pidDebugDeviceInterface.h"

#include "../../../common/commons.h"

#include "../../../common/cmd/commonCommand.h"
#include "../../../common/eeprom/eeprom.h"
#include "../../../common/error/error.h"

#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

#include "../../../common/io/reader.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../device/device.h"
#include "../../../motion/parameters/motionParameterDebug.h"
#include "../../../motion/pid/pidDebug.h"
#include "../../../motion/pid/parameters/pidParameterDebug.h"
#include "../../../motion/pid/endDetection/motionEndDetectionDebug.h"

static PidMotion* pidMotion;

bool isPidDebugDeviceOk(void) {
    return true;
}

void initPidDebugDevice(void) {
}

void stopPidDebugDevice(void) {

}

void devicePidDebugHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
	// MOTION PARAMETERS DEBUG
    if (commandHeader == COMMAND_MOTION_PARAMETERS_DEBUG) {
		// send acknowledge
		ackCommand(outputStream, PID_DEBUG_DEVICE_HEADER, COMMAND_MOTION_PARAMETERS_DEBUG);
		OutputStream* debugOutputStream = getDebugOutputStreamLogger();
		printMotionParameterList(debugOutputStream);
	}
    // PID DEBUG
    else if (commandHeader == COMMAND_END_MOTION_DEBUG) {
        ackCommand(outputStream, PID_DEBUG_DEVICE_HEADER, COMMAND_END_MOTION_DEBUG);
        OutputStream* debugOutputStream = getDebugOutputStreamLogger();
        printMotionEndDetectionParameter(debugOutputStream, &(pidMotion->globalParameters.motionEndDetectionParameter));
        printMotionEndInfos(debugOutputStream, pidMotion);
    }
	else if (commandHeader == COMMAND_DEBUG_DATA_PID_CONSOLE) {
		ackCommand(outputStream, PID_DEBUG_DEVICE_HEADER, COMMAND_DEBUG_DATA_PID_CONSOLE);
		OutputStream* debugOutputStream = getDebugOutputStreamLogger();
		printPidDataDebugTable(debugOutputStream, pidMotion);
	}
	else if (commandHeader == COMMAND_PID_MOTION_INSTRUCTION_TABLE) {
		ackCommand(outputStream, PID_DEBUG_DEVICE_HEADER, COMMAND_PID_MOTION_INSTRUCTION_TABLE);
		OutputStream* debugOutputStream = getDebugOutputStreamLogger();
		printMotionInstructionTable(debugOutputStream, pidMotion);
	}
	else if (commandHeader == COMMAND_DEBUG_PID_PARAMETERS) {
		ackCommand(outputStream, PID_DEBUG_DEVICE_HEADER, COMMAND_DEBUG_PID_PARAMETERS);
		OutputStream* debugOutputStream = getDebugOutputStreamLogger();
		printAllPidParametersTable(debugOutputStream, pidMotion);
	}
}

static DeviceDescriptor descriptor = {
    .deviceInit = &initPidDebugDevice,
    .deviceShutDown = &stopPidDebugDevice,
    .deviceIsOk = &isPidDebugDeviceOk,
    .deviceHandleRawData = &devicePidDebugHandleRawData,
};

DeviceDescriptor* getPidDebugDeviceDescriptor(PidMotion* pidMotionParam) {
	pidMotion = pidMotionParam;
    return &descriptor;
}
