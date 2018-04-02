#ifndef COLOR_SENSOR_PC_H
#define COLOR_SENSOR_PC_H

#include "../colorSensor.h"

/** 
 * Init a fake color Sensor Pc so that we could simulate it.
 * @param colorSensor the pointer (simulates POO)
 * @param pColor pointer on an color Structure value to store the value which is used to store the value
 */
void initColorSensorPc(ColorSensor* colorSensor, Color* pColor);

#endif
