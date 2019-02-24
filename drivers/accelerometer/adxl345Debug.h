#ifndef ADXL435_DEBUG_H
#define ADXL435_DEBUG_H

#include "adxl345.h"

#include "../../common/sensor/accelerometer/accelerometer.h"

// DEBUG

#define ADXL345_DEBUG_REG_COLUMN_LENGTH	             10
#define ADXL345_DEBUG_REG_HEX_COLUMN_LENGTH	         10
#define ADXL345_DEBUG_REG_NAME_COLUMN_LENGTH	     20
#define ADXL345_DEBUG_REG_RW_COLUMN_LENGTH	         10
#define ADXL345_DEBUG_REG_VALUE_DEC_COLUMN_LENGTH	 10
#define ADXL345_DEBUG_REG_VALUE_HEX_COLUMN_LENGTH	 10
#define ADXL345_DEBUG_REG_VALUE_BIN_COLUMN_LENGTH	 15
#define ADXL345_DEBUG_REG_VALUE_MG_COLUMN_LENGTH	 20

/**
 * Debug the main register list of the ADX1345 (but not the data).
 * @param outputStream
 * @param i2cBusConnection
 */
void adxl345_debugMainRegisterList(OutputStream* outputStream, Accelerometer* accelerometer);

/**
 * Read then debug the Data value stored in AccelerometerData
 * @param outputStream
 * @param i2cBusConnection
 * @param accelerometerData
 */
void adxl345_debugValueRegisterList(OutputStream* outputStream, Accelerometer* accelerometer);

// void adxl345_debugValueRegisterListIfShock(OutputStream* outputStream, I2cBusConnection* i2cBusConnection, AccelerometerData* accelerometerData);


#endif
