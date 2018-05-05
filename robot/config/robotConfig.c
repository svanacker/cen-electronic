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

