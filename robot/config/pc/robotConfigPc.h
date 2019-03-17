#ifndef ROBOT_CONFIG_PC_H
#define ROBOT_CONFIG_PC_H

#include "../robotConfig.h"

#define ROBOT_CONFIG_PC_FILE_NAME                      "robotConfigPc.txt"
#define ROBOT_CONFIG_PC_FILE_LENGTH                                     18

/**
 * Initialize a type of robotConfig for Windows
 * @param robotConfig a pointer of RobotConfig type.
 */
void initRobotConfigPc(RobotConfig* robotConfig, enum RobotType robotType);

#endif
