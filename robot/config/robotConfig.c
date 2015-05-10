#include "robotConfig.h"

void initRobotConfig(RobotConfig* robotConfig,
                robotConfigReadIntFunction* robotConfigReadInt, robotConfigWriteIntFunction* robotConfigWriteInt){
    robotConfig->robotConfigReadInt = robotConfigReadInt;
    robotConfig->robotConfigWriteInt = robotConfigWriteInt;
}
