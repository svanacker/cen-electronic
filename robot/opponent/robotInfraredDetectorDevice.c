#include "robotInfraredDetector.h"
#include "robotInfraredDetectorDeviceInterface.h"

#include "../../common/commons.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../device/device.h"

#include "../../main/meca2/mechanicalBoard2.h"

static RobotInfraredDetector* robotInfraredDetector;

void deviceRobotInfraredDetectorInit(void) {
    initRobotInfraredDetector(robotInfraredDetector);
}

void deviceRobotInfraredDetectorShutDown(void) {
}

bool deviceRobotInfraredDetectorIsOk(void) {
    return true;
}

void notifyInfraredDetectorDetection(enum InfraredDetectorGroupType type) {
    // Notify OutputStream
    Buffer* buffer = getMechanicalBoard2I2CSlaveOutputBuffer();
    OutputStream* notifyOutputStream = getOutputStream(buffer);
    append(notifyOutputStream, NOTIFY_INFRARED_DETECTOR_DETECTION);
    appendHex2(notifyOutputStream, type);

    // Debug
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    append(debugOutputStream, NOTIFY_INFRARED_DETECTOR_DETECTION);
    appendHex2(debugOutputStream, type);
}

void deviceRobotInfraredDetectorHandleRawData(char commandHeader,
        InputStream* inputStream,
        OutputStream* outputStream) {
    // Command to ask to enable notification
    if (commandHeader == DETECTOR_ENABLE_NOTIFICATION_COMMAND) {
        ackCommand(outputStream, ROBOT_INFRARED_DETECTOR_DEVICE_HEADER, DETECTOR_ENABLE_NOTIFICATION_COMMAND);
        enum InfraredDetectorGroupType type = readHex2(inputStream);
        setInfraredRobotNotification(type, true);
    }
    else if (commandHeader == DETECTOR_DISABLE_NOTIFICATION_COMMAND) {
        ackCommand(outputStream, ROBOT_INFRARED_DETECTOR_DEVICE_HEADER, DETECTOR_DISABLE_NOTIFICATION_COMMAND);
        enum InfraredDetectorGroupType type = readHex2(inputStream);
        setInfraredRobotNotification(type, false);
    }
    // Read if it detects
    else if (commandHeader == COMMAND_INFRARED_DETECTOR_DETECTION) {
        ackCommand(outputStream, ROBOT_INFRARED_DETECTOR_DEVICE_HEADER, COMMAND_INFRARED_DETECTOR_DETECTION);

        enum InfraredDetectorGroupType type = readHex2(inputStream);
        bool hasDetected;
        if (type == DETECTOR_GROUP_TYPE_FORWARD) {
            hasDetected = getRobotInfraredObstacleForward();
        }
        else {
            hasDetected = getRobotInfraredObstacleBackward();
        }
        
        // Send argument
        if (hasDetected) {
            appendHex2(outputStream, 1);
        }
        else {
            appendHex2(outputStream, 0);
        }
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceRobotInfraredDetectorInit,
    .deviceShutDown = &deviceRobotInfraredDetectorShutDown,
    .deviceIsOk = &deviceRobotInfraredDetectorIsOk,
    .deviceHandleRawData = &deviceRobotInfraredDetectorHandleRawData,
};

DeviceDescriptor* getRobotInfraredDetectorDeviceDescriptor(RobotInfraredDetector* robotInfraredDetectorParam) {
    robotInfraredDetector = robotInfraredDetectorParam;
    return &descriptor;
}
