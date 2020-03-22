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

#endif
