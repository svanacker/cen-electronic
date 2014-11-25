#include "robotConfigPic32.h"

#include "../../robot/config/robotConfig.h"



/**
 * Implementation of the read Function of configuration switch.
 * @see robotConfig.h
 * @private
 */

void _robotConfigReadInt (RobotConfig* robotConfig){

}


void initRobotConfigPic32(RobotConfig* robotConfig) {
    initRobotConfig(robotConfig, _robotConfigReadInt);
}