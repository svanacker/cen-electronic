#include <stdbool.h>

#include "codersDevice.h"
#include "codersDeviceInterface.h"

#include "../../../common/delay/cenDelay.h"

#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../motion/position/coders.h"
#include "../../../motion/position/trajectory.h"

#include "../../../robot/kinematics/robotKinematics.h"

void stopCoders(void) {

}

bool isCodersDeviceOk(void) {
    return true;
}

#define CODERS_DEVICE_NAME_COLUMN_LENGTH			5
#define CODERS_DEVICE_PULSE_DEC_COLUMN_LENGTH		10
#define CODERS_DEVICE_PULSE_HEX_COLUMN_LENGTH		12
#define CODERS_DEVICE_DISTANCE__COLUMN_LENGTH		9
#define CODERS_DEVICE_LAST_COLUMN_LENGTH            40

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
}

void printCoderTable(OutputStream* outputStream) {
	printCoderListHeader(outputStream);
	signed long coderValue0 = getCoderValue(CODER_LEFT);
	signed long coderValue1 = getCoderValue(CODER_RIGHT);

	RobotKinematics* robotKinematics = getRobotKinematics();
	float leftWheelLengthForOnePulse = getLeftWheelLengthForOnePulse(robotKinematics);
	float rightWheelLengthForOnePulse = getLeftWheelLengthForOnePulse(robotKinematics);

	printCoderDebug(outputStream, "left", coderValue0, leftWheelLengthForOnePulse);
	printCoderDebug(outputStream, "right", coderValue1, rightWheelLengthForOnePulse);
	appendTableHeaderSeparatorLine(outputStream);
}

void deviceCodersHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream) {
    if (commandHeader == COMMAND_GET_WHEEL_POSITION) {
        ackCommand(outputStream, CODERS_DEVICE_HEADER, COMMAND_GET_WHEEL_POSITION);
        
        signed long coderValue0 = getCoderValue(CODER_LEFT);
        signed long coderValue1 = getCoderValue(CODER_RIGHT);

        appendHex8(outputStream, coderValue0);
        appendSeparator(outputStream);
        appendHex8(outputStream, coderValue1);
    } else if (commandHeader == COMMAND_DEBUG_GET_WHEEL_POSITION) {
        ackCommand(outputStream, CODERS_DEVICE_HEADER, COMMAND_DEBUG_GET_WHEEL_POSITION);

        OutputStream* debugOutputStream = getDebugOutputStreamLogger();
		printCoderTable(debugOutputStream);
    } else if (commandHeader == COMMAND_DEBUG_TIMER_GET_WHEEL_POSITION) {
		ackCommand(outputStream, CODERS_DEVICE_HEADER, COMMAND_DEBUG_TIMER_GET_WHEEL_POSITION);
		unsigned int durationInDeciSec = readHex2(inputStream);
		checkIsSeparator(inputStream);
		unsigned int iterationCount = readHex2(inputStream);
		OutputStream* debugOutputStream = getDebugOutputStreamLogger();

		unsigned int i;
		for (i = 0; i < iterationCount; i++) {
			printCoderTable(debugOutputStream);
			delaymSec(100);
		}
	}
	else if (commandHeader == COMMAND_CLEAR_CODERS) {
        ackCommand(outputStream, CODERS_DEVICE_HEADER, COMMAND_CLEAR_CODERS);

        updateTrajectoryAndClearCoders();
    }
}


static DeviceDescriptor descriptor = {
    .deviceInit = &initCoders,
    .deviceShutDown = &stopCoders,
    .deviceIsOk = &isCodersDeviceOk,
    .deviceHandleRawData = &deviceCodersHandleRawData,
};

DeviceDescriptor* getCodersDeviceDescriptor(void) {
    return &descriptor;
}
