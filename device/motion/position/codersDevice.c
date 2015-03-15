#include <stdbool.h>

#include "codersDevice.h"
#include "codersDeviceInterface.h"

#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

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

void printCoderDebug(OutputStream* outputStream, char* name, signed long value, float wheelFactor) {
    appendString(outputStream, name);
    append(outputStream, ':');

    appendStringAndDec(outputStream, "pulseDec=", value);

    appendString(outputStream, ", pulseHex=");
    appendHex4(outputStream, value);

    appendStringAndDecf(outputStream, ", dist=", ((float) value) * wheelFactor);
    appendString(outputStream, " mm");
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

        signed long coderValue0 = getCoderValue(CODER_LEFT);
        signed long coderValue1 = getCoderValue(CODER_RIGHT);

        RobotKinematics* robotKinematics = getRobotKinematics();
        float leftWheelLengthForOnePulse = getLeftWheelLengthForOnePulse(robotKinematics);
        float rightWheelLengthForOnePulse = getLeftWheelLengthForOnePulse(robotKinematics);

        appendCRLF(debugOutputStream);
        printCoderDebug(debugOutputStream, "left", coderValue0, leftWheelLengthForOnePulse);
        appendCRLF(debugOutputStream);
        printCoderDebug(debugOutputStream, "right", coderValue1, rightWheelLengthForOnePulse);
    } else if (commandHeader == COMMAND_CLEAR_CODERS) {
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
