#ifndef COLOR_SENSOR_TCS34725_H
#define COLOR_SENSOR_TCS34725_H

#include "colorSensor.h"
#include "tcs34725.h"
#include "../../../common/color/color.h"

/**
 * Init the Tcs34725 as a color Sensor Structure (POO Management)
 * @param colorSensor
 * @param pColor
 */
void initColorSensorTcs34725(ColorSensor* colorSensor, Color* color, Tcs34725* tcs34725);

#endif
