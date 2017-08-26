#include <stdbool.h>

#include "trajectoryDevice.h"

#include "trajectoryDeviceInterface.h"

#include "../../../common/commons.h"

#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/math/cenMath.h"

#include "../../../motion/position/trajectory.h"

// Device Interface

void initTrajectoryDevice(void) {
    initializeTrajectory();
}

void stopTrajectoryDevice(void) {

}

bool isTrajectoryDeviceOk(void) {
    return true;
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
    if (header == COMMAND_TRAJECTORY_GET_ABSOLUTE_POSITION) {
        ackCommand(outputStream, TRAJECTORY_DEVICE_HEADER, COMMAND_TRAJECTORY_GET_ABSOLUTE_POSITION);

        updateTrajectoryWithNoThreshold();
        notifyAbsolutePositionWithoutHeader(outputStream);

    }
    else if (header == COMMAND_TRAJECTORY_DEBUG_GET_ABSOLUTE_POSITION) {
        ackCommand(outputStream, TRAJECTORY_DEVICE_HEADER, COMMAND_TRAJECTORY_DEBUG_GET_ABSOLUTE_POSITION);

        updateTrajectoryWithNoThreshold();

        OutputStream* debugOutputStream = getAlwaysOutputStreamLogger();
        printDebugPosition(debugOutputStream);
    }
	else if (header == COMMAND_TRAJECTORY_DEBUG_CODERS) {
		ackCommand(outputStream, TRAJECTORY_DEVICE_HEADER, COMMAND_TRAJECTORY_DEBUG_CODERS);

		updateTrajectoryWithNoThreshold();

		OutputStream* debugOutputStream = getAlwaysOutputStreamLogger();
		printDebugCoderHistory(debugOutputStream);
	}
    else if (header == COMMAND_TRAJECTORY_SET_ABSOLUTE_POSITION) {
        long newX = readHex4(inputStream);
        inputStream->readChar(inputStream);
        long newY = readHex4(inputStream);
        inputStream->readChar(inputStream);
        long newAngle = readHex4(inputStream);

        ackCommand(outputStream, TRAJECTORY_DEVICE_HEADER, COMMAND_TRAJECTORY_SET_ABSOLUTE_POSITION);

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
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &initializeTrajectory,
    .deviceShutDown = &stopTrajectoryDevice,
    .deviceIsOk = &isTrajectoryDeviceOk,
    .deviceHandleRawData = &deviceTrajectoryHandleRawData
};

DeviceDescriptor* getTrajectoryDeviceDescriptor(void) {
    return &descriptor;
}
