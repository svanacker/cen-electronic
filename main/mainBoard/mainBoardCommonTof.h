#ifndef MAIN_BOARD_COMMON_TOF_H
#define MAIN_BOARD_COMMON_TOF_H

#include "mainBoardCommon.h"

#include "../../common/i2c/i2cBusList.h"

#include "../../drivers/tof/tofList.h"

// TOFS
#define MAIN_BOARD_TOF_SENSOR_LIST_LENGTH                                     14

/**
 * Device Tof Initialization of MAIN_BOARD.
 */
void mainBoardCommonTofAddDevices(void);

/**
 * Main Part of MAIN_BOARD for Tof initialization (Driver).
 * @param i2cBus
 * @param tofSensorCount how many tof we initialize (even we could handle more)
 * Useful when we just want to initialize 2 tof like for Experience 2019 Main
 * Program.
 */
void mainBoardCommonTofInitDrivers(I2cBus* i2cBus, I2cBus* i2cBus2, unsigned int tofSensorCount);

/**
 * Returns the list of Tof Sensor.
 */
TofSensorList* mainBoardCommonTofGetTofSensorList(void);

#endif
