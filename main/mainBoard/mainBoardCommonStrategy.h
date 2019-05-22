#ifndef MAIN_BOARD_COMMON_POSITION_H
#define MAIN_BOARD_COMMON_POSITION_H

#include "mainBoardCommon.h"

#include "../../robot/config/robotConfig.h"

#include "../../robot/strategy/gameStrategyContext.h"

/**
 * Add the devices linked to the strategy.
 * @param portIndex
 */
void mainBoardCommonStrategyAddDevices(unsigned char portIndex);

/**
 * Handle Stream instruction linked to the strategy
 */
void mainBoardCommonStrategyHandleStreamInstruction();

/**
 * Main Board Strategy Driver Init Part.
 */
GameStrategyContext* mainBoardCommonStrategyMainInitDrivers(RobotConfig* robotConfig);

/**
 * Main Board Strategy Init Part (After the Drivers Init).
 */
void mainBoardCommonStrategyMainEndInit(void);

// LOOP

void mainBoardCommonStrategyMainLoop(void);

#endif
