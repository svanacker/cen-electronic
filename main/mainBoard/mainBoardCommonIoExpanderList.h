#ifndef MAIN_BOARD_COMMON_IO_EXPANDER_LIST_H
#define MAIN_BOARD_COMMON_IO_EXPANDER_LIST_H

#include "mainBoardCommon.h"

#include "../../robot/config/robotConfig.h"

#include "../../drivers/ioExpander/ioExpander.h"
#include "../../drivers/ioExpander/ioExpanderList.h"

/**
 * Device IO Expander List Initialization of MAIN_BOARD 32.
 */
void mainBoardCommonIOExpanderListAddDevices32(void);

/**
 * Main Part of MAIN_BOARD for IO Expander List.
 */
IOExpanderList* mainBoardCommonIOExpanderListInitDrivers32(RobotConfig* robotConfig);

/**
 * To get a reference on the initialized IOEXpanderList.
 */
IOExpanderList* mainBoardCommonGetIOExpanderList(void);


#endif