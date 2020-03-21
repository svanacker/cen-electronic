#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "fakeRobotDevice.h"
#include "fakeRobotDeviceInterface.h"

#include "../../../common/2d/2d.h"

#include "../../../common/delay/cenDelay.h"

#include "../../../common/error/error.h"

#include "../../../common/io/buffer.h"
#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/reader.h"
#include "../../../common/io/printWriter.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/loggerDebug.h"
#include "../../../common/log/logLevel.h"
#include "../../../common/log/logHandler.h"

#include "../../../device/device.h"
#include "../../../device/deviceDescriptor.h"
#include "../../../device/deviceList.h"
#include "../../../device/deviceDebug.h"
#include "../../../device/deviceUsage.h"
#include "../../../device/transmitMode.h"

#include "../../../robot/fake/fakeRobot.h"

static FakeRobot* fakeRobot;

void deviceFakeRobotInit(void) {
}

void deviceFakeRobotShutDown(void) {
}

bool deviceFakeRobotIsOk(void) {
    return true;
}

void deviceFakeRobotHandleRawData(unsigned char header, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    if (header == COMMAND_FAKE_ROBOT_GET_POSITION) {
        // data
        ackCommand(outputStream, FAKE_ROBOT_DEVICE_HEADER, COMMAND_FAKE_ROBOT_GET_POSITION);
        appendHex4(outputStream, (unsigned int) fakeRobot->x);
        appendSeparator(outputStream);
        appendHex4(outputStream, (unsigned int) fakeRobot->y);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, fakeRobot->angleRadian, ANGLE_DIGIT_DEGREE_PRECISION);
        appendSeparator(outputStream);
        appendHex4(outputStream, (unsigned int) fakeRobot->radius);
        appendSeparator(outputStream);
    } else if (header == COMMAND_FAKE_ROBOT_SET_POSITION) {
        // data
        ackCommand(outputStream, FAKE_ROBOT_DEVICE_HEADER, COMMAND_FAKE_ROBOT_SET_POSITION);

        fakeRobot->x = (float) readHex4(inputStream);
        checkIsSeparator(inputStream);
        fakeRobot->y = (float) readHex4(inputStream);
        checkIsSeparator(inputStream);
        fakeRobot->angleRadian = (float) readHex4(inputStream);
        checkIsSeparator(inputStream);
        fakeRobot->radius = (float) readHex4(inputStream);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceFakeRobotInit,
    .deviceShutDown = &deviceFakeRobotShutDown,
    .deviceIsOk = &deviceFakeRobotIsOk,
    .deviceHandleRawData = &deviceFakeRobotHandleRawData,
};

DeviceDescriptor* getFakeRobotDeviceDescriptor(FakeRobot* fakeRobotParam) {
    fakeRobot = fakeRobotParam;
    return &descriptor;
}
