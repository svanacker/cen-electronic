#ifndef COLOR_SENSOR_DEBUG_H
#define COLOR_SENSOR_DEBUG_H

#include "colorSensor.h"

#include "../../common/io/outputStream.h"

/**
 * Print a the state of the color Sensor as a table.
 */
void printColorSensorTable(OutputStream* outputStream, ColorSensor* colorSensor);

#endif
