#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

/**
 * get the value from the temperature sensor
 * @return temperature  the value from the temperature sensor
 */
char getTemperatureSensor (void);

void setTemperatureAlertLimit(int TemperatureSensorAlert);

#endif
