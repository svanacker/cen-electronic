// SENSOR CURRENT
#ifndef INA3221_H
#define INA3221_H

#include "../../../common/sensor/current/current.h"

#include "../../../common/i2c/i2cCommon.h"

#define INA3221_CONFIGURATION_SENSOR_REGISTER                              0x01
#define INA3221_OVER_CURRENT_SENSOR_REGISTER                               0x03

#define INA3221_DELTA                                                        40 //40mV
#define INA3221_SHUNT                                                       100 // 100 mOhms

#define INA3221_CONFIGURATION                                                 0
#define INA3221_CHANNEL1_SHUNT_VOLTAGE                                        1
#define INA3221_CHANNEL1_BUS_VOLTAGE                                          2
#define INA3221_CHANNEL2_SHUNT_VOLTAGE                                        3
#define INA3221_CHANNEL2_BUS_VOLTAGE                                          4
#define INA3221_CHANNEL3_SHUNT_VOLTAGE                                        5
#define INA3221_CHANNEL3_BUS_VOLTAGE                                          6
#define INA3221_CHANNEL1_CRITICAL_ALERT_LIMIT                                 7
#define INA3221_CHANNEL1_WARNING_ALERT_LIMIT                                  8
#define INA3221_CHANNEL2_CRITICAL_ALERT_LIMIT                                 9
#define INA3221_CHANNEL2_WARNING_ALERT_LIMIT                               0x0A
#define INA3221_CHANNEL3_CRITICAL_ALERT_LIMIT                              0x0B
#define INA3221_CHANNEL3_WARNING_ALERT_LIMIT                               0x0C
#define INA3221_SHUNT_VOLTAGE_SUM                                          0x0D
#define INA3221_SHUNT_VOLTAGE_SUM_LIMIT                                    0x0E
#define INA3221_MASK_ENABLE                                                0x0F
#define INA3221_POWER_VALID_UPPER_LIMIT                                    0x10
#define INA3221_POWER_VALID_LOWER_LIMIT                                    0x11
#define INA3221_MANUFACTURER_ID                                            0xFE
#define INA3221_DLE_ID                                                     0xFF


// Overtemp Shutdown output
//  0  OS active LOW
//  1  OS active HIGH
#define INA3221_OS_POLARITY_LOW                                            0x00
#define INA3221_OS_POLARITY_HIGH                                           0x04

/**
 * Initializes a current structure for a INA3221 sensor.
 * @param current a pointer on the current object (POO simulation)
 * @param i2cBusConnection a pointer on the i2cBusConnection
 */
void initCurrentINA3221(Current* current, I2cBusConnection* i2cBusConnection);

#endif
