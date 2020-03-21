#ifndef TOF_NETWORK_VL53L0X_H
#define TOF_NETWORK_VL53L0X_H

#include "tof_vl53l0x.h"

#include "../tof.h"

#include "../../../common/i2c/i2cBusConnectionList.h"

#include <stdbool.h>
#include "vl53l0x_def.h"
#include "vl53l0x_platform.h"

/**
 * Extract the bus Connection from the TofSensor.
 * @param tofSensorVL53L0X
 * @param debug
 * @return 
 */
I2cBusConnection* getTofSensorVL53L0XI2cBusConnection(TofSensor* tofSensor);

/**
 * @private
 * @param tofSensor
 * @param multiplexerList
 * @param tofI2cSlaveAddress
 * @param debug
 * @return 
 */
I2cBusConnection* tofSensorSelectRightI2cBusConnection(TofSensor* tofSensor,
        unsigned char tofI2cSlaveAddress,
        bool debug);
/**
 * Change the address of the current Time of Flight
 * @param newAddr
 * @return 
 */
bool tofSetAddress(TofSensorVL53L0X* tofSensorVL53L0X, I2cBusConnection* i2cBusConnection, unsigned int newAddress);

bool tofSensorChangeAddressIfNeeded(TofSensor* tofSensor);

#endif