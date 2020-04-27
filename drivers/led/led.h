#ifndef LED_H
#define LED_H

#include <stdbool.h>

#include "../../common/color/color.h"

// forward declaration
struct LedArray;
typedef struct LedArray LedArray;

/**
 * Type of function to initialize the led array.
 */
typedef bool LedArrayInitFunction(LedArray* ledArray);

/**
 * Write the color (RGB) value of the specified led.
 * @param ledIndex the index of the led
 * @param R the R value of the RGB value
 * @param G the G value of the RGB value
 * @param B the B value of the RGB value
 */
typedef void LedArrayWriteValueFunction(LedArray* ledArray, unsigned int ledIndex, unsigned int R, unsigned int G, unsigned int B);

/**
 * Read the color (RGB) value of the specified led.
 * @param ledIndex the index of the led
 * @return the result of the color
 */
typedef Color LedArrayReadValueFunction(LedArray* ledArray, unsigned int ledIndex);

/**
 * Defines the contract for led Array.
 */
struct LedArray {
    /** A flag to know if the structure was already initialized */
    bool initialized;
    /** How man led are available */
    int ledCount;
    /** The function which must be used to init the led Array */
    LedArrayInitFunction* ledArrayInit;
    /** The function which must be used to read the value of the led array */
    LedArrayReadValueFunction* ledArrayReadValue;
    /** The function which must be used to write the value of the led array */
    LedArrayWriteValueFunction* ledArrayWriteValue;
    /** pointer on other object (useful for I2C Connection for example) .*/
    int* object;
};

/** 
 * Init the wrapper around Led Array. 
 */
void initLedArray(LedArray* ledArray,
        int ledCount,
        LedArrayInitFunction* ledArrayInit,
        LedArrayReadValueFunction* ledArrayReadValue,
        LedArrayWriteValueFunction* ledArrayWriteValue,
        int* object);

/**
 * Change the color of the led with a color object
 * @param ledArray the encapsulation of object (POO Paradigm)
 * @param ledIndex the index of the led
 * @param color the color (RGB) that we would like to apply
 */
void setLedColor(LedArray* ledArray, unsigned int ledIndex, Color color);

/**
 * Converts a distance in cm as an equivalence in terms of color.
 * The distance is between 0 (RED) and (127 and more) (GREEN)
 * Between 0 and 25 cm, 
 *   RED = 255,                 
 *   GREEN = distance * 10,
 *   BLUE = 0
 * Between 26 and 50,
 *   RED = 255 - (distance - 25) * 10
 *   GREEN = 255
 *   BLUE = 0
 * Between 50 and 75,
 *   RED = 0,
 *   GREEN = 255,
 *   BLUE = (distance - 50) * 10
 * Between 75 and 100
 *   RED = 0
 *   GREEN = 255 - (distance - 75) * 10
 *   BLUE = 255
 * > 100 
 *   RED = 0
 *   GREEN = 0
 *   BLUE = 255
 */
void setLedColorAsDistance(LedArray* ledArray, unsigned int ledIndex, unsigned int distance);

#endif
