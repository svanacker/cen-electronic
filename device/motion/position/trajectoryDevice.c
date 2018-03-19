#include <stdbool.h>

#include "trajectoryDevice.h"

#include "trajectoryDeviceInterface.h"

#include "../../../common/commons.h"

#include "../../../common/2d/2d.h"

#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/math/cenMath.h"

#include "../../../motion/position/trajectory.h"
#include "../../../motion/position/trajectoryDebug.h"

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
    appendHexFloat6(outputStream, p->pos.x, POSITION_DIGIT_MM_PRECISION);
    appendSeparator(outputStream);
    appendHexFloat6(outputStream, p->pos.y, POSITION_DIGIT_MM_PRECISION);
    appendSeparator(outputStream);
    appendHexFloat4(outputStream, radToDeg(p->orientation), ANGLE_DIGIT_DEGREE_PRECISION);
}

void deviceTrajectoryHandleRawData(char header,
        InputStream* inputStream,
        OutputStream* outputStream,
        OutputStream* notificationOutputStream) {
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
        float newX = readHexFloat6(inputStream, POSITION_DIGIT_MM_PRECISION);
        checkIsSeparator(inputStream);
        float newY = readHexFloat6(inputStream, POSITION_DIGIT_MM_PRECISION);
        checkIsSeparator(inputStream);
        float newAngle = readHexFloat4(inputStream, ANGLE_DIGIT_DEGREE_PRECISION);

        ackCommand(outputStream, TRAJECTORY_DEVICE_HEADER, COMMAND_TRAJECTORY_SET_ABSOLUTE_POSITION);

        OutputStream* debugOutputStream = getDebugOutputStreamLogger();

        float fX = (float) newX;
        float fY = (float) newY;
        float fAngle = degToRad(newAngle);

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
