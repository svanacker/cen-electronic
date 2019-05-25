#ifndef TOF_VL53L0X_H
#define TOF_VL53L0X_H

#include "../tof.h"

#include "../../../common/i2c/i2cBusConnectionList.h"

#include <stdbool.h>
#include "vl53l0x_def.h"
#include "vl53l0x_platform.h"

// Forward declaration
typedef struct TofSensorVL53L0X TofSensorVL53L0X;

/**
 * Specific structure about the Tof Sensor specific to the VL53L0X.
 */
struct TofSensorVL53L0X {
    VL53L0X_Error                      status;
    VL53L0X_Dev_t                      device;
    VL53L0X_Version_t                  version;
    VL53L0X_DeviceInfo_t               deviceInfo;
    VL53L0X_RangingMeasurementData_t   rangingMeasurementData;
    I2cBusConnection*                  i2cBusConnection;
};

/**
 * Extract the TofSensorVL53L0X from the TofSensor structure.
 * @param tofSensor
 * @return 
 */
TofSensorVL53L0X* getTofSensorVL53L0X(TofSensor* tofSensor);

/**
 * Start the use of the Time Of Flight
 * @param debug
 * @return 
 */
bool tof_vl53l0x_begin(TofSensorVL53L0X* tofSensorVL53L0X, bool debug);

/**
 * Change the address of the current Time of Flight
 * @param newAddr
 * @return 
 */
bool tofSetAddress(TofSensorVL53L0X* tofSensorVL53L0X, I2cBusConnection* i2cBusConnection, unsigned int newAddress);

/**
 * Get the status of the time of Flight Sensor
 * @return 
 */
VL53L0X_Error tofGetStatus(TofSensorVL53L0X* tofSensorVL53L0X);
/**
 * Show the data of the measurement
 * @param pRangingMeasurementData
 */
void printRangeStatus(VL53L0X_RangingMeasurementData_t* pRangingMeasurementData);

// TOF OBJECT IMPLEMENTATION (POO)

/**
 * INitialize the Structure of Data, but does not start really the tofSensor
 * @param tofSensor
 * @param tofSensorVL53L0X
 * @param i2cBusConnection
 * @return 
 */
void initTofSensorVL53L0X(TofSensor* tofSensor,
                    TofSensorVL53L0X* tofSensorVL53L0X);


#endif