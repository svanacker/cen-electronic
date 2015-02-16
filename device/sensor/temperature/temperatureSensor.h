#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include "../../../common/i2c/i2cCommon.h"

/**
 * get the value from the temperature sensor
 * @return temperature  the value from the temperature sensor
 */
char getTemperatureSensor (I2cBus* i2cBus);

void setTemperatureAlertLimit(I2cBus* i2cBus, int TemperatureSensorAlert);

#endif
