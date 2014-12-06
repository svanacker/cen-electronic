#include "robotConfig.h"

void initRobotConfig(RobotConfig* robotConfig,
                robotConfigReadIntFunction* robotConfigReadInt){
    robotConfig->robotConfigReadInt = robotConfigReadInt;
}
