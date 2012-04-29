#include "trajectoryDevice.h"

#include "trajectoryDeviceInterface.h"

#include "../../../common/commons.h"

#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"
#include "../../../common/io/stream.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/math/cenMath.h"

#include "../../../motion/position/trajectory.h"

// Device Interface

void initTrajectoryDevice() {
    initializeTrajectory();
}

void stopTrajectoryDevice() {

}

unsigned int isTrajectoryDeviceOk(void) {
    return 1;
}

void notifyAbsolutePositionWithoutHeader(OutputStream* outputStream) {
    Position* p = getPosition();
    appendHexFloat4(outputStream, p->pos.x, 1);
    appendSeparator(outputStream);
    appendHexFloat4(outputStream, p->pos.y, 1);
    appendSeparator(outputStream);
    appendHexFloat4(outputStream, p->orientation / PI_DIVIDE_1800, 1);
}

void deviceTrajectoryHandleRawData(char header,
        InputStream* inputStream,
        OutputStream* outputStream) {
    if (header == COMMAND_GET_ABSOLUTE_POSITION) {
        appendAck(outputStream);

        updateTrajectoryWithNoThreshold();
        append(outputStream, COMMAND_GET_ABSOLUTE_POSITION);
        notifyAbsolutePositionWithoutHeader(outputStream);

    }
    else if (header == COMMAND_DEBUG_GET_ABSOLUTE_POSITION) {
        appendAck(outputStream);

        updateTrajectoryWithNoThreshold();
        append(outputStream, COMMAND_DEBUG_GET_ABSOLUTE_POSITION);

        OutputStream* debugOutputStream = getOutputStreamLogger(ALWAYS);
        printPosition(debugOutputStream);
    }

    else if (header == COMMAND_SET_ABSOLUTE_POSITION) {
        long newX = readHex4(inputStream);
        inputStream->readChar(inputStream);
        long newY = readHex4(inputStream);
        inputStream->readChar(inputStream);
        long newAngle = readHex4(inputStream);

        appendAck(outputStream);

        OutputStream* debugOutputStream = getDebugOutputStreamLogger();

        appendStringAndDec(debugOutputStream, "newX=", newX);
        appendStringAndDec(debugOutputStream, ",newY=", newY);
        appendStringAndDec(debugOutputStream, ",newAngle=", newAngle);

        float fX = (float) newX;
        float fY = (float) newY;
        float fAngle = PI_DIVIDE_1800 * (float) newAngle;

        appendStringAndDecf(debugOutputStream, "fX=", fX);
        appendStringAndDecf(debugOutputStream, ",fY=", fY);
        appendStringAndDecf(debugOutputStream, ",fAngle=", fAngle);

        setPosition(fX, fY, fAngle);

        append(outputStream, COMMAND_SET_ABSOLUTE_POSITION);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &initializeTrajectory,
    .deviceShutDown = &stopTrajectoryDevice,
    .deviceIsOk = &isTrajectoryDeviceOk,
    .deviceHandleRawData = &deviceTrajectoryHandleRawData
};

DeviceDescriptor* getTrajectoryDeviceDescriptor() {
    return &descriptor;
}
