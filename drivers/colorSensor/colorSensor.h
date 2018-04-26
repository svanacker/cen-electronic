#ifndef COLOR_SENSOR_H
#define COLOR_SENSOR_H

#include <stdbool.h>

#include "../../common/color/color.h"

// forward declaration
struct ColorSensor;
typedef struct ColorSensor ColorSensor;

/**
 * Type of function to initialize the color sensor.
 */
typedef bool colorSensorInitFunction(ColorSensor* colorSensor);

/**
* Read the color (RGB) value of the specified color Sensor.
* @return the value of the colorSensor
*/
typedef Color* colorSensorReadValueFunction(ColorSensor* colorSensor);

/**
 * Read the color (RGB) and determine a type of color
 */
typedef enum ColorType colorSensorFindColorTypeFunction(ColorSensor* colorSensor);

/**
* Defines the contract for switch robot configuration.
*/
struct ColorSensor {
    /** The function which must be used to init the color Sensor */
    colorSensorInitFunction* colorSensorInit;
    /** The function which must be used to read the value of the color Sensor */
    colorSensorReadValueFunction* colorSensorReadValue;
    /** The function which find a specific color . */
    colorSensorFindColorTypeFunction* colorSensorFindColorType;
    /** The color value object (result of last read) */
    Color* color;
    /** pointer on other object (useful for I2C Connection for example) .*/
    int* object;
};

/** 
 * Init the wrapper around Color Sensor. 
 */
void initColorSensor(ColorSensor* colorSensor, 
               colorSensorInitFunction* colorSensorInit,
               colorSensorReadValueFunction* colorSensorReadValue,
               colorSensorFindColorTypeFunction* colorSensorFindColorType,
               Color* color,
               int* object);

#endif
