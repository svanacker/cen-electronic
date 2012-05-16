#include "robotInfraredDetector.h"
#include "robotInfraredDetectorDeviceInterface.h"

#include "../../common/commons.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../device/device.h"

void deviceRobotInfraredDetectorInit() {
    initRobotInfraredDetector();
}

void deviceRobotInfraredDetectorShutDown() {
}

BOOL deviceRobotInfraredDetectorIsOk() {
    return TRUE;
}

void deviceRobotInfraredDetectorHandleRawData(char header,
        InputStream* inputStream,
        OutputStream* outputStream) {
    if (header == COMMAND_INFRARED_DETECTOR_DETECTION) {
        appendAck(outputStream);
        append(outputStream, COMMAND_INFRARED_DETECTOR_DETECTION);

		BOOL hasDetected = getRobotInfraredObstacle();
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
