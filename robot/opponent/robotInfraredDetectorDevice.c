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

void deviceRobotInfraredDetectorInit() {
    initRobotInfraredDetector();
}

void deviceRobotInfraredDetectorShutDown() {
}

bool deviceRobotInfraredDetectorIsOk() {
    return true;
}

void notifyInfraredDetectorDetection(int type) {
    Buffer* buffer = getMechanicalBoard2I2CSlaveOutputBuffer();
    OutputStream* outputStream = getOutputStream(buffer);
    append(outputStream, NOTIFY_INFRARED_DETECTOR_DETECTION);
    appendHex2(outputStream, type);

    // Debug
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    append(debugOutputStream, NOTIFY_INFRARED_DETECTOR_DETECTION);
    appendHex2(debugOutputStream, type);
}

void deviceRobotInfraredDetectorHandleRawData(char commandHeader,
        InputStream* inputStream,
        OutputStream* outputStream) {
    // Command to ask
    if (commandHeader == COMMAND_INFRARED_DETECTOR_DETECTION) {
        appendAck(outputStream);
        append(outputStream, COMMAND_INFRARED_DETECTOR_DETECTION);

        int type = readHex2(inputStream);
        bool hasDetected;
        if (type == DETECTOR_FORWARD_INDEX) {
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

DeviceDescriptor* getRobotInfraredDetectorDeviceDescriptor() {
    return &descriptor;
}
