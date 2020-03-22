#include "ledPca9685.h"

#include "../led.h"

#include "../../../common/i2c/i2cBusConnectionList.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/log/logger.h"

#include "../../../drivers/pwm/servo/pca9685.h"

#include <stdbool.h>
#include <stdlib.h>

I2cBusConnection* getLedArrayI2cBusConnection(LedArray* ledArray) {
    return (I2cBusConnection*) ledArray->object;
}

/**
 * Initialize the led array implemented by a PCA9685.
 */
bool ledArrayInitPca9685(LedArray* ledArray) {
    // avoid to initialize several time
    if (ledArray->initialized) {
        return true;
    }
    ledArray->initialized = true;
    I2cBusConnection* i2cBusConnection = getLedArrayI2cBusConnection(ledArray);
    pca9685_init(i2cBusConnection);

    return true;
}

/**
 * Pca9685 Implementation Read the color (RGB) value of the specified led.
 * @param ledIndex the index of the led
 * @return the current color
 */
Color ledArrayReadValuePca9685(LedArray* ledArray, unsigned int ledIndex) {
    // TODO
    // I2cBusConnection* i2cBusConnection = getLedArrayI2cBusConnection(ledArray);
    // TODO : Implementation
    Color result;
    result.R = 0;
    result.G = 0;
    result.B = 0;

    return result;
}


/**
 * Pca9685 Implementation Write the color (RGB) value of the specified led.
 * @param ledIndex the index of the led
 */
void ledArrayWriteValuePca9685(LedArray* ledArray, unsigned int ledIndex, unsigned int R, unsigned int G, unsigned int B) {
    I2cBusConnection* i2cBusConnection = getLedArrayI2cBusConnection(ledArray);
    pca9685_setPWM(i2cBusConnection, ledIndex * 3, 4095 - B * 16, B * 16);
    pca9685_setPWM(i2cBusConnection, ledIndex * 3 + 1, 4095 - G * 16, G * 16);
    pca9685_setPWM(i2cBusConnection, ledIndex * 3 + 2, 4095 - R * 16, R * 16);
}

void initLedArrayPca9685(LedArray* ledArray, I2cBusConnection* i2cBusConnection) {
    initLedArray(ledArray, &ledArrayInitPca9685, &ledArrayReadValuePca9685, &ledArrayWriteValuePca9685, (int*) i2cBusConnection);
}
