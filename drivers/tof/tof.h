#ifndef TOF_H
#define TOF_H

#include <stdbool.h>
#include "vl53l0x/vl53l0x_def.h"

/**
 * Start the use of the Time Of Flight
 * @param i2c_addr
 * @param debug
 * @return 
 */
bool tofBegin(uint8_t i2c_addr, bool debug);

/**
 * Change the address of the current Time of Flight
 * @param newAddr
 * @return 
 */
bool tofSetAddress(uint8_t newAddr);

/**
 * Get the status of the time of Flight Sensor
 * @return 
 */
VL53L0X_Error tofGetStatus();

/**
 * Do a single ranging Measurement
 * @param pRangingMeasurementData the pointer with information to measure
 * @param debug if we want to debug or not
 * @return 
 */
VL53L0X_Error getSingleRangingMeasurement(VL53L0X_RangingMeasurementData_t* pRangingMeasurementData, bool debug);

/**
 * Show the data of the measurement
 * @param pRangingMeasurementData
 */
void printRangeStatus(VL53L0X_RangingMeasurementData_t* pRangingMeasurementData);


#endif