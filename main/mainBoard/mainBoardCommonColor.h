#ifndef MAIN_BOARD_COMMON_COLOR_H
#define MAIN_BOARD_COMMON_COLOR_H

#include "mainBoardCommon.h"

#include "../../drivers/colorSensor/colorSensor.h"

/**
 * Color Sensor Initialization of MAIN_BOARD 32.
 */
void mainBoardCommonColorSensorAddDevices(void);

/**
 * Main Part of MAIN_BOARD for Color Sensor.
 */
ColorSensor* mainBoardCommonColorSensorInitDrivers();

/**
 * To get a reference on the initialized Sensor.
 */
ColorSensor* mainBoardCommonGetColorSensor(void);


#endif