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

/** Config is a 16 bit value. We store the value here */
static unsigned int config = 0;

void refreshConfig(void) {
    config = robotConfig->robotConfigReadInt(robotConfig);
}

int isConfigSet(unsigned int configMask) {
    refreshConfig();
    int intersection = (config & configMask);
    return intersection != 0;
}

unsigned int getConfigValue(void) {
    refreshConfig();
    return config;
}

char* getConfigBitString(unsigned char configIndex) {
    switch (configIndex) {
    case CONFIG_DONT_USE_BEACON_MASK: return "DontUseBeacon";
    case CONFIG_ROLLING_TEST_MASK: return "RollingTest";
    case CONFIG_COLOR_GREEN_MASK: return "Green";
    default: return "?";
    }
}

unsigned char isConfigBalise() {
    refreshConfig();
    return !isConfigSet(CONFIG_DONT_USE_BEACON_MASK);
}

unsigned char getStrategy() {
    refreshConfig();
    return config & CONFIG_STRATEGY_MASK;
}

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

void deviceRobotConfigHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream) {
    if (commandHeader == COMMAND_GET_CONFIG) {
        // can take a little time
        refreshConfig();
        ackCommand(outputStream, ROBOT_CONFIG_DEVICE_HEADER, COMMAND_GET_CONFIG);
        appendHex4(outputStream, config);
    }
    else if (commandHeader == COMMAND_SET_CONFIG) {
        ackCommand(outputStream, ROBOT_CONFIG_DEVICE_HEADER, COMMAND_SET_CONFIG);
        config = readHex4(inputStream);
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
