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
typedef void LedArrayWriteValueFunction(LedArray* ledArray, unsigned int ledIndex, unsigned char R, unsigned char G, unsigned char B);

/**
 * Defines the contract for led Array.
 */
struct LedArray {
    /** The function which must be used to init the led Array */
    LedArrayInitFunction* ledArrayInit;
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
        LedArrayWriteValueFunction* ledArrayWriteValue,
        int* object);

#endif
