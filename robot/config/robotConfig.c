#include "robotConfig.h"
#include <stdbool.h>

#include "../../common/io/binaryPrintWriter.h"
#include "../../common/io/outputStream.h"

#include "../../common/io/printWriter.h"

void initRobotConfig(RobotConfig* robotConfig,
                     enum RobotType robotType, 
                robotConfigReadIntFunction* robotConfigReadInt, robotConfigWriteIntFunction* robotConfigWriteInt){
    robotConfig->robotType = robotType;
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

bool isSonarActivated(RobotConfig* robotConfig) {
    return isConfigSet(robotConfig, CONFIG_SONAR_FAR_MASK | CONFIG_SONAR_NEAR_MASK);
}
