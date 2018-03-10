#include <stdbool.h>

#include "codersDevice.h"
#include "codersDeviceInterface.h"

#include "../../../common/error/error.h"

#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../motion/position/coders.h"
#include "../../../motion/position/codersDebug.h"
#include "../../../motion/position/trajectory.h"

void stopCoders(void) {

}

bool isCodersDeviceOk(void) {
    return true;
}

void initDeviceCoders(void) {
    initCoders();
}

void deviceCodersHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    if (commandHeader == COMMAND_GET_WHEEL_POSITION) {
        ackCommand(outputStream, CODERS_DEVICE_HEADER, COMMAND_GET_WHEEL_POSITION);
        updateTrajectory();
        signed long coderValue0 = getCoderValue(CODER_LEFT);
        signed long coderValue1 = getCoderValue(CODER_RIGHT);

        appendHex8(outputStream, coderValue0);
        appendSeparator(outputStream);
        appendHex8(outputStream, coderValue1);
    } else if (commandHeader == COMMAND_DEBUG_GET_WHEEL_POSITION) {
        ackCommand(outputStream, CODERS_DEVICE_HEADER, COMMAND_DEBUG_GET_WHEEL_POSITION);

        OutputStream* debugOutputStream = getDebugOutputStreamLogger();
        updateTrajectory();

		printCoderTable(debugOutputStream);
    } else if (commandHeader == COMMAND_DEBUG_TIMER_GET_WHEEL_POSITION) {
		ackCommand(outputStream, CODERS_DEVICE_HEADER, COMMAND_DEBUG_TIMER_GET_WHEEL_POSITION);
		unsigned int durationInDeciSec = readHex2(inputStream);
		checkIsSeparator(inputStream);
        unsigned int coderDebugIterationCount = readHex2(inputStream);
        enableCoderDebug(durationInDeciSec, coderDebugIterationCount);
	}
	else if (commandHeader == COMMAND_CLEAR_CODERS) {
        ackCommand(outputStream, CODERS_DEVICE_HEADER, COMMAND_CLEAR_CODERS);

        updateTrajectoryAndClearCoders();
    }
}


static DeviceDescriptor descriptor = {
    .deviceInit = &initDeviceCoders,
    .deviceShutDown = &stopCoders,
    .deviceIsOk = &isCodersDeviceOk,
    .deviceHandleRawData = &deviceCodersHandleRawData,
};

DeviceDescriptor* getCodersDeviceDescriptor(void) {
    return &descriptor;
}
