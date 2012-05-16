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

#include "../../main/meca2/mechanicalBoard2.h"

void deviceRobotInfraredDetectorInit() {
    initRobotInfraredDetector();
}

void deviceRobotInfraredDetectorShutDown() {
}

BOOL deviceRobotInfraredDetectorIsOk() {
    return TRUE;
}

void notifyInfraredDetectorDetection() {
    Buffer* buffer = getMechanicalBoard2I2CSlaveOutputBuffer();
    OutputStream* outputStream = getOutputStream(buffer);
	OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    append(outputStream, NOTIFY_INFRARED_DETECTOR_DETECTION);
	append(debugOutputStream, NOTIFY_INFRARED_DETECTOR_DETECTION);
}

void deviceRobotInfraredDetectorHandleRawData(char header,
        InputStream* inputStream,
        OutputStream* outputStream) {
	// Command to ask
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
