#include "robotConfig.h"
#include <stdbool.h>

#include "../../common/io/binaryPrintWriter.h"
#include "../../common/io/outputStream.h"

#include "../../common/io/printWriter.h"

void initRobotConfig(RobotConfig* robotConfig,
                robotConfigReadIntFunction* robotConfigReadInt, robotConfigWriteIntFunction* robotConfigWriteInt){
    robotConfig->robotConfigReadInt = robotConfigReadInt;
    robotConfig->robotConfigWriteInt = robotConfigWriteInt;
}

bool isConfigSet(RobotConfig* robotConfig, unsigned int configMask) {
    unsigned int config = getConfigValue(robotConfig);
    int intersection = (config & configMask);
    return intersection != 0;
}

unsigned int getConfigValue(RobotConfig* robotConfig) {
    return robotConfig->robotConfigReadInt(robotConfig);;
}

char* getConfigBitString(RobotConfig* robotConfig, unsigned char configIndex) {
    switch (configIndex) {
        case CONFIG_DONT_USE_BEACON_MASK: return "DontUseBeacon";
        case CONFIG_ROLLING_TEST_MASK: return "RollingTest";
        case CONFIG_COLOR_GREEN_MASK: return "Green";
        default: return "?";
    }
}
