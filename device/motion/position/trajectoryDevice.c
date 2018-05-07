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

        OutputStream* debugOutputStream = getDebugOutputStreamLogger();
        printDebugPosition(debugOutputStream);
    }
	else if (header == COMMAND_TRAJECTORY_DEBUG_CODERS) {
		ackCommand(outputStream, TRAJECTORY_DEVICE_HEADER, COMMAND_TRAJECTORY_DEBUG_CODERS);

		updateTrajectoryWithNoThreshold();

		OutputStream* debugOutputStream = getDebugOutputStreamLogger();
		printDebugCoderHistory(debugOutputStream);
	}
    else if (header == COMMAND_TRAJECTORY_SET_ABSOLUTE_POSITION) {
        float newX = readHexFloat6(inputStream, POSITION_DIGIT_MM_PRECISION);
        checkIsSeparator(inputStream);
        float newY = readHexFloat6(inputStream, POSITION_DIGIT_MM_PRECISION);
        checkIsSeparator(inputStream);
        float newAngle = readHexFloat4(inputStream, ANGLE_DIGIT_DEGREE_PRECISION);

        ackCommand(outputStream, TRAJECTORY_DEVICE_HEADER, COMMAND_TRAJECTORY_SET_ABSOLUTE_POSITION);

        float fX = (float) newX;
        float fY = (float) newY;
        float fAngle = degToRad(newAngle);

        // We must ensure are not in 
        setPosition(fX, fY, fAngle);
    }
    // Adjust Angle / X / Y
    else if (header == COMMAND_TRAJECTORY_ADJUST_ANGLE_TO_CLOSEST) {
        ackCommand(outputStream, TRAJECTORY_DEVICE_HEADER, COMMAND_TRAJECTORY_ADJUST_ANGLE_TO_CLOSEST);
        checkIsSeparator(inputStream);
        bool done = adjustAngle(TRAJECTORY_DEVICE_ADJUST_ANGLE_THRESHOLD );
        appendBool(outputStream, done);
    }
    else if (header == COMMAND_TRAJECTORY_ADJUST_X) {
        ackCommand(outputStream, TRAJECTORY_DEVICE_HEADER, COMMAND_TRAJECTORY_ADJUST_X);
        float newX = readHexFloat6(inputStream, COMMAND_TRAJECTORY_ADJUST_X);
        checkIsSeparator(inputStream);
        bool done = adjustXPosition(newX, TRAJECTORY_DEVICE_ADJUST_DISTANCE_THRESHOLD);
        appendBool(outputStream, done);
    }
    else if (header == COMMAND_TRAJECTORY_ADJUST_Y) {
        ackCommand(outputStream, TRAJECTORY_DEVICE_HEADER, COMMAND_TRAJECTORY_ADJUST_Y);       
        float newY = readHexFloat6(inputStream, COMMAND_TRAJECTORY_ADJUST_Y);
        checkIsSeparator(inputStream);
        bool done = adjustXPosition(newY, TRAJECTORY_DEVICE_ADJUST_DISTANCE_THRESHOLD);
        appendBool(outputStream, done);
    }
    // NOTIFY SYSTEM
    else if (header == COMMAND_TRAJECTORY_NOTIFY_OFF) {
        ackCommand(outputStream, TRAJECTORY_DEVICE_HEADER, COMMAND_TRAJECTORY_NOTIFY_OFF);       
        TrajectoryInfo* trajectory = getTrajectory();
        trajectory->notifyChange = false;
    }
    else if (header == COMMAND_TRAJECTORY_NOTIFY_ON) {
        ackCommand(outputStream, TRAJECTORY_DEVICE_HEADER, COMMAND_TRAJECTORY_NOTIFY_ON);       
        TrajectoryInfo* trajectory = getTrajectory();
        trajectory->notifyChange = true;
    }
    else if (header == COMMAND_TRAJECTORY_NOTIFY_SET_PARAMETERS) {
        ackCommand(outputStream, TRAJECTORY_DEVICE_HEADER, COMMAND_TRAJECTORY_NOTIFY_SET_PARAMETERS);       
        TrajectoryInfo* trajectory = getTrajectory();
        trajectory->thresholdDistance = readHexFloat4(inputStream, POSITION_DIGIT_MM_PRECISION);
        checkIsSeparator(inputStream);
        trajectory->thresholdAngleRadian = degToRad(readHexFloat4(inputStream, ANGLE_DIGIT_DEGREE_PRECISION));
    }
}

// NOTIFICATION

bool trajectoryNotifyIfEnabledAndTreshold(OutputStream* notificationOutputStream) {
    TrajectoryInfo* trajectory = getTrajectory();
    if (!trajectory->notifyChange) {
        return false;
    }
    // We do not accept if threshold are too small to avoid to saturate the link
    if (trajectory->thresholdDistance < 5.0f || trajectory->thresholdAngleRadian < 0.02f) {
        return false;
    }
    float distanceSinceLastNotification = getDistanceBetweenLastNotificationAndCurrentRobotPosition();
    float absoluteAngleRadianSinceLastNotification = getAbsoluteAngleRadianBetweenLastNotificationAndCurrentRobotPosition();
    
    if (distanceSinceLastNotification > trajectory->thresholdDistance
        || absoluteAngleRadianSinceLastNotification > trajectory->thresholdAngleRadian) {
        /*
        OutputStream* debugOutputStream = getDebugOutputStreamLogger();
        appendStringAndDecf(debugOutputStream, "distanceSinceLastNotification:", distanceSinceLastNotification);
        println(debugOutputStream);
        appendStringAndDecf(debugOutputStream, "absoluteAngleRadianSinceLastNotification:", distanceSinceLastNotification);
        println(debugOutputStream);
        */
        Position* p = getPosition();
        append(notificationOutputStream, TRAJECTORY_DEVICE_HEADER);
        append(notificationOutputStream, NOTIFY_TRAJECTORY_CHANGED);
        // XXXXXX-YYYYYY-AAAA
        notifyAbsolutePositionWithoutHeader(notificationOutputStream);
        // We must add "Trajectory Type"
        enum TrajectoryType trajectoryType = computeTrajectoryType(distanceSinceLastNotification, absoluteAngleRadianSinceLastNotification);
        appendSeparator(notificationOutputStream);
        appendHex2(notificationOutputStream, trajectoryType);
        clearLastNotificationData();
        return true;
    }
    return false;
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
