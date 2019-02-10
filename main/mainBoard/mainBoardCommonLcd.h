#ifndef MAIN_BOARD_COMMON_LCD_H
#define MAIN_BOARD_COMMON_LCD_H

#include "mainBoardCommon.h"

#include "../../robot/config/robotConfig.h"

/**
 * Add the devices linked to Lcd
 */
void mainBoardCommonLcdAddDevices(void);

/**
 * Init the LCD and use or not the backlight
 * @param robotConfig
 */
void mainBoardCommonLcdInit(RobotConfig* robotConfig);

#endif
