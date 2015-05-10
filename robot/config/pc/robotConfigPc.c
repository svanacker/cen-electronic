#include "robotConfigPc.h"

#include "../robotConfig.h"

static unsigned int robotConfigValue;

/**
 * Implementation of the read Function of configuration switch.
 * @see robotConfig.h
 * @private
 */
unsigned int _robotConfigPcReadInt(RobotConfig* robotConfig) {
    return robotConfigValue;
}

/**
* Implementation of the write Function of configuration switch.
* @see robotConfig.h
* @private
*/
void _robotConfigPcWriteInt(RobotConfig* robotConfig, unsigned int value) {
    robotConfigValue = value;
}

void initRobotConfigPc(RobotConfig* robotConfig) {
    initRobotConfig(robotConfig, _robotConfigPcReadInt, _robotConfigPcWriteInt);
}
