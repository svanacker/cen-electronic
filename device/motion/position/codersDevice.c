#include "codersDevice.h"
#include "codersDeviceInterface.h"

#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/stream.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../motion/position/coders.h"
#include "../../../motion/position/trajectory.h"

#include "../../../robot/robotConstants.h"

void stopCoders(void) {

}

unsigned int isCodersDeviceOk(void) {
    return 1;
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

void deviceCodersHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    if (header == COMMAND_GET_WHEEL_POSITION) {
        appendAck(outputStream);
        signed long coderValue0 = getCoderValue(CODER_LEFT);
        signed long coderValue1 = getCoderValue(CODER_RIGHT);

        // Send the two position
        append(outputStream, COMMAND_GET_WHEEL_POSITION);

        appendHex8(outputStream, coderValue0);
        appendSeparator(outputStream);
        appendHex8(outputStream, coderValue1);
    } else if (header == COMMAND_DEBUG_GET_WHEEL_POSITION) {
        appendAck(outputStream);
        append(outputStream, COMMAND_DEBUG_GET_WHEEL_POSITION);

        OutputStream* debugOutputStream = getDebugOutputStreamLogger();

        signed long coderValue0 = getCoderValue(CODER_LEFT);
        signed long coderValue1 = getCoderValue(CODER_RIGHT);

        appendCRLF(debugOutputStream);
        printCoderDebug(debugOutputStream, "left", coderValue0, WHEEL_LENGTH_LEFT);
        appendCRLF(debugOutputStream);
        printCoderDebug(debugOutputStream, "right", coderValue1, WHEEL_LENGTH_RIGHT);
    } else if (header == COMMAND_CLEAR_CODERS) {
        appendAck(outputStream);

        updateTrajectoryAndClearCoders();
        append(outputStream, COMMAND_CLEAR_CODERS);
    }
}


static DeviceDescriptor descriptor = {
    .deviceInit = &initCoders,
    .deviceShutDown = &stopCoders,
    .deviceIsOk = &isCodersDeviceOk,
    .deviceHandleRawData = &deviceCodersHandleRawData,
};

DeviceDescriptor* getCodersDeviceDescriptor() {
    return &descriptor;
}
