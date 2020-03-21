#ifndef LED_PCA9685_H
#define LED_PCA9685_H

#include "../../../common/i2c/i2cBusConnectionList.h"

#include "../led.h"

#include <stdbool.h>

/**
 * Init a Led Array Implementation for PCA9685.
 * @param ledArray POO Paradigm
 * @param i2cBusConnection the i2cBusConnection
 */
void initLedArrayPca9685(LedArray* ledArray, I2cBusConnection* i2cBusConnection);

#endif

