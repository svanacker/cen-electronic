#ifndef TOF_RANGING_VL53L0X_H
#define TOF_RANGING_VL53L0X_H

#include "tof_vl53l0x.h"
#include "../tof.h"

#include "../../../common/i2c/i2cBusConnectionList.h"

#include <stdbool.h>
#include "vl53l0x_def.h"
#include "vl53l0x_platform.h"

#include "../../../drivers/i2c/multiplexer/multiplexer.h"

/**
 * Do a single ranging Measurement
 * @param debug if we want to debug or not
 * @return 
 */
VL53L0X_Error getSingleRangingMeasurement(TofSensorVL53L0X* tofSensorVL53L0X, bool debug);

/**
 * Tof POO Implementation for VL53L0X.
 * Not private, but must not be used outside init program.
 */
unsigned int tofSensorGetDistanceVL53L0XMM(TofSensor* tofSensor);

#endif