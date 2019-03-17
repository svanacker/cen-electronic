#ifndef ROBOT_CONFIG_PIC32_H
#define ROBOT_CONFIG_PIC32_H

#include "../robotConfig.h"

/**
 * Initialize a type of robotConfig
 * @param robotConfig a pointer of RobotConfig type.
 * @param robotType the enum for robot Type (Big, Small ...)
 */
void initRobotConfigPic32(RobotConfig* robotConfig, enum RobotType robotType);

#endif
