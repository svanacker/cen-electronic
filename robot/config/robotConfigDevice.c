#include <stdlib.h>

#include "robotConfig.h"
#include "robotConfigDevice.h"
#include "robotConfigDeviceInterface.h"


#include "../../common/cmd/commonCommand.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../device/device.h"

#include "../../drivers/driver.h"

static RobotConfig* robotConfig;

// Device interface

void deviceRobotConfigInit(void) {
    //refreshConfig();
}

void deviceRobotConfigShutDown(void) {

}

bool isRobotConfigDeviceOk(void) {
    //refreshConfig();
    //return getConfigValue() < MAX_UNSIGNEDINT;
    return true;
}

void deviceRobotConfigHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    if (commandHeader == COMMAND_GET_CONFIG) {
        // can take a little time
        unsigned int config = getConfigValue(robotConfig);
        ackCommand(outputStream, ROBOT_CONFIG_DEVICE_HEADER, COMMAND_GET_CONFIG);
        appendHex4(outputStream, config);
    }
    else if (commandHeader == COMMAND_SET_CONFIG) {
        ackCommand(outputStream, ROBOT_CONFIG_DEVICE_HEADER, COMMAND_SET_CONFIG);
        unsigned int config = readHex4(inputStream);
        if (robotConfig->robotConfigWriteInt != NULL) {
            robotConfig->robotConfigWriteInt(robotConfig, config);
        }
    }
	else if (commandHeader == COMMAND_CONFIG_DEBUG) {
		ackCommand(outputStream, ROBOT_CONFIG_DEVICE_HEADER, COMMAND_CONFIG_DEBUG);
		printRobotTableConfig(getInfoOutputStreamLogger(), robotConfig);
	}
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceRobotConfigInit,
    .deviceShutDown = &deviceRobotConfigShutDown,
    .deviceIsOk = &isRobotConfigDeviceOk,
    .deviceHandleRawData = &deviceRobotConfigHandleRawData
};

DeviceDescriptor* getRobotConfigDeviceDescriptor(RobotConfig* robotConfigParam) {
    robotConfig = robotConfigParam;
    return &descriptor;
}
