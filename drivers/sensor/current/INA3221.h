// SENSOR CURRENT
#ifndef INA3221_H
#define INA3221_H

#include "../../../common/sensor/current/current.h"

#include "../../../common/i2c/i2cCommon.h"

#define INA3221_CONFIGURATION_SENSOR_REGISTER     0x01
#define INA3221_OVER_CURRENT_SENSOR_REGISTER   0x03

#define DELTA 40 //40mV
#define SHUNT 100 // 100 mOhms

#define CONFIGURATION 0
#define CHANNEL1_SHUNT_VOLTAGE 1
#define CHANNEL1_BUS_VOLTAGE 2
#define CHANNEL2_SHUNT_VOLTAGE 3
#define CHANNEL2_BUS_VOLTAGE 4
#define CHANNEL3_SHUNT_VOLTAGE 5
#define CHANNEL3_BUS_VOLTAGE 6
#define CHANNEL1_CRITICAL_ALERT_LIMIT 7
#define CHANNEL1_WARNING_ALERT_LIMIT 8
#define CHANNEL2_CRITICAL_ALERT_LIMIT 9
#define CHANNEL2_WARNING_ALERT_LIMIT 0X0A
#define CHANNEL3_CRITICAL_ALERT_LIMIT 0X0B
#define CHANNEL3_WARNING_ALERT_LIMIT 0X0C
#define SHUNT_VOLTAGE_SUM 0X0D
#define SHUNT_VOLTAGE_SUM_LIMIT 0X0E
#define MASK_ENABLE 0X0F
#define POWER_VALID_UPPER_LIMIT 0X10
#define POWER_VALID_LOWER_LIMIT 0X11
#define MANUFACTURER_ID 0XFE
#define DLE_ID 0XFF


// Overtemp Shutdown output
//  0  OS active LOW
//  1  OS active HIGH
#define OS_POLARITY_LOW 0x00
#define OS_POLARITY_HIGH 0x04

/**
 * Initializes a current structure for a INA3221 sensor.
 * @param current a pointer on the current object (POO simulation)
 * @param i2cBusConnection a pointer on the i2cBusConnection
 */
void initCurrentINA3221(Current* current, I2cBusConnection* i2cBusConnection);

#endif
