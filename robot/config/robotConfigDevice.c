#include "robotConfig.h"
#include "robotConfigDevice.h"
#include "robotConfigDeviceInterface.h"


#include "../../common/cmd/commonCommand.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../device/device.h"

#include "../../drivers/driver.h"

static RobotConfig* robotConfig;

/** Config is a 16 bit value */
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
        case CONFIG_USE_BALISE_MASK: return "UseBalise";
        case CONFIG_USE_SONAR_MASK: return "UseSonar";
        case CONFIG_ROLLING_TEST_MASK: return "RollingTest";
        case CONFIG_COLOR_BLUE_MASK: return "Blue";
        default: return "?";
    }
}

/**
 * Returns a String corresponding to the configuration
 * '1' when the bit is set, '0' when not set
 */
void appendStringConfig(OutputStream* outputStream) {
    refreshConfig();
    signed int i;
    for (i = CONFIG_BIT_COUNT - 1; i >= 0; i--) {
        char c;
        if ((config & (1 << i)) > 0) {
            c = '1';
        }
        else {
            c = '0';
        }
        append(outputStream, c);
    }
}

unsigned char isConfigBalise() {
    refreshConfig();
    return isConfigSet(CONFIG_USE_BALISE_MASK);
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

void deviceRobotConfigHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    if (header == COMMAND_CONFIG) {
        // can take a little time
        refreshConfig();  
        ackCommand(outputStream, ROBOT_CONFIG_DEVICE_HEADER, COMMAND_CONFIG);
        appendHex4(outputStream, config);     
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
