#ifndef INA219_DEBUG_H
#define INA219_DEBUG_H

#include "ina219.h"

#include "../../common/sensor/accelerometer/accelerometer.h"

// DEBUG

#define INA219_DEBUG_REG_COLUMN_LENGTH	             10
#define INA219_DEBUG_REG_HEX_COLUMN_LENGTH	         10
#define INA219_DEBUG_REG_NAME_COLUMN_LENGTH	         20
#define INA219_DEBUG_REG_RW_COLUMN_LENGTH	         10
#define INA219_DEBUG_REG_VALUE_DEC_COLUMN_LENGTH	 10
#define INA219_DEBUG_REG_VALUE_HEX_COLUMN_LENGTH	 10
#define INA219_DEBUG_REG_VALUE_BIN_COLUMN_LENGTH	 15
#define INA219_DEBUG_REG_VALUE_MG_COLUMN_LENGTH	     20

/**
 * Debug the main register list of the INA219 (but not the data).
 * @param outputStream
 * @param i2cBusConnection
 */
void ina219_debugRegisterList(OutputStream* outputStream, Accelerometer* accelerometer);

#endif
