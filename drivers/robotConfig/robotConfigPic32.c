#include "robotConfigPic32.h"

#include "../../robot/config/robotConfig.h"



/**
 * Implementation of the read Function of configuration switch.
 * @see robotConfig.h
 * @private
 */

signed int _robotConfigReadInt (RobotConfig* robotConfig){
    return (0x43);
}


void initRobotConfigPic32(RobotConfig* robotConfig) {
    initRobotConfig(robotConfig, _robotConfigReadInt);
}