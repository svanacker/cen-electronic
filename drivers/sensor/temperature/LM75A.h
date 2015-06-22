// SENSOR TEMPERATURE
#ifndef LM75A_H
#define LM75A_H

#include "../../../common/sensor/temperature/temperature.h"

#include "../../../common/i2c/i2cCommon.h"

#define LM75A_READ_SENSOR_REGISTER              0x00
#define LM75A_CONFIGURATION_SENSOR_REGISTER     0x01
#define LM75A_HYSTERESIS_SENSOR_REGISTER        0x02
#define LM75A_OVER_TEMPERATURE_SENSOR_REGISTER   0x03

// Overtemp Shutdown output
//  0  OS active LOW
//  1  OS active HIGH
#define OS_POLARITY_LOW 0x00
#define OS_POLARITY_HIGH 0x04

/**
 * Initializes a temperature structure for a LM75A sensor.
 * @param temperature a pointer on the temperature object (POO simulation)
 * @param i2cBusConnection a pointer on the i2cBusConnection
 */
void initTemperatureLM75A(Temperature* temperature, I2cBusConnection* i2cBusConnection);

#endif

