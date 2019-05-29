#ifndef MAIN_BOARD_COMMON_TOF_32_H
#define MAIN_BOARD_COMMON_TOF_32_H

#include "mainBoardCommon.h"

#include "../../robot/config/robotConfig.h"

/**
 * Device Tof Initialization of MAIN_BOARD 32.
 */
void mainBoardCommonTofAddDevices32(void);

/**
 * Main Part of MAIN_BOARD for Tof initialization (Driver).
 * Useful when we just want to initialize 2 tof like for Experience 2019 Main
 * Program.
 */
void mainBoardCommonTofInitDrivers32(RobotConfig* robotConfig);

#endif
