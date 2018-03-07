#include <stdbool.h>

#include "codersDevice.h"
#include "codersDeviceInterface.h"

#include "../../../common/delay/cenDelay.h"

#include "../../../common/error/error.h"

#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/timer/cenTimer.h"
#include "../../../common/timer/timerConstants.h"
#include "../../../common/timer/timerList.h"

#include "../../../motion/position/coders.h"
#include "../../../motion/position/trajectory.h"

#include "../../../robot/kinematics/robotKinematics.h"

void stopCoders(void) {

}

bool isCodersDeviceOk(void) {
    return true;
}

#define CODERS_DEVICE_NAME_COLUMN_LENGTH			8
#define CODERS_DEVICE_PULSE_DEC_COLUMN_LENGTH		15
#define CODERS_DEVICE_PULSE_HEX_COLUMN_LENGTH		15
#define CODERS_DEVICE_DISTANCE__COLUMN_LENGTH		10
#define CODERS_DEVICE_LAST_COLUMN_LENGTH            35

static unsigned int coderDebugIterationCount;

/**
* Private.
*/
void printCoderListHeader(OutputStream* outputStream) {
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "coder", CODERS_DEVICE_NAME_COLUMN_LENGTH);
	appendStringHeader(outputStream, "pulse (Dec)", CODERS_DEVICE_PULSE_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "pulse (Hex)", CODERS_DEVICE_PULSE_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "dist (mm)", CODERS_DEVICE_DISTANCE__COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, CODERS_DEVICE_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);
}


void printCoderDebug(OutputStream* outputStream, char* name, signed long value, float wheelFactor) {
	appendStringTableData(outputStream, name, CODERS_DEVICE_NAME_COLUMN_LENGTH);
	appendDecTableData(outputStream, value, CODERS_DEVICE_PULSE_DEC_COLUMN_LENGTH);
	appendHex6TableData(outputStream, value, CODERS_DEVICE_PULSE_DEC_COLUMN_LENGTH);
	float dist = ((float)value) * wheelFactor;
	appendDecfTableData(outputStream, dist, CODERS_DEVICE_PULSE_DEC_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, CODERS_DEVICE_LAST_COLUMN_LENGTH);
}

void printCoderTable(OutputStream* outputStream) {
	println(outputStream);
	printCoderListHeader(outputStream);
	signed long coderValue0 = getCoderValue(CODER_LEFT);
	signed long coderValue1 = getCoderValue(CODER_RIGHT);

	RobotKinematics* robotKinematics = getRobotKinematics();
	float leftWheelLengthForOnePulse = getCoderLeftWheelLengthForOnePulse(robotKinematics);
	float rightWheelLengthForOnePulse = getCoderRightWheelLengthForOnePulse(robotKinematics);

	printCoderDebug(outputStream, "left", coderValue0, leftWheelLengthForOnePulse);
	printCoderDebug(outputStream, "right", coderValue1, rightWheelLengthForOnePulse);
	appendTableHeaderSeparatorLine(outputStream);
}

/**
* Callback.
*/
void debugGetWheelCallback(Timer* timer) {
    if (coderDebugIterationCount <= 0) {
        return;
    }
    updateTrajectory();
    coderDebugIterationCount--;
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();

    printCoderTable(debugOutputStream);
}

void initDeviceCoders(void) {
    initCoders();
    addTimer(CODERS_TIMER_INDEX, TIME_DIVIDER_1_HERTZ, &debugGetWheelCallback, "CODERS TIMER", NULL);
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
		Timer* timer = getTimerByCode(CODERS_TIMER_INDEX);
		if (timer == NULL) {
			writeError(CODERS_TIMER_NOT_FOUND);
			return;
		}
		unsigned int durationInDeciSec = readHex2(inputStream);
		checkIsSeparator(inputStream);
		coderDebugIterationCount = readHex2(inputStream);
		timer->timeDiviser = TIME_DIVIDER_10_HERTZ * durationInDeciSec;
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
