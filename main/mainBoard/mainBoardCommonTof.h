#ifndef MAIN_BOARD_COMMON_TOF_H
#define MAIN_BOARD_COMMON_TOF_H

#include "mainBoardCommon.h"

#include "../../common/i2c/i2cBusList.h"

#include "../../drivers/tof/tofList.h"

/**
 * Device Tof Initialization of MAIN_BOARD.
 */
void mainBoardCommonTofAddDevices(void);

/**
 * Main Part of MAIN_BOARD for Tof initialization (Driver).
 * @param i2cBus
 */
void mainBoardCommonTofInitDrivers(I2cBus* i2cBus);

/**
 * Returns the list of Tof Sensor.
 */
TofSensorList* mainBoardCommonTofGetTofSensorList(void);

#endif
