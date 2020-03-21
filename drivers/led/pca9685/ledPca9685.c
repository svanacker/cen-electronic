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
    I2cBusConnection* i2cBusConnection = getLedArrayI2cBusConnection(ledArray);
    pca9685_init(i2cBusConnection);

    return true;
}

/**
 * Pca9685 Implementation Write the color (RGB) value of the specified led.
 * @param ledIndex the index of the led
 */
void ledArrayWriteValuePca9685(LedArray* ledArray, unsigned int ledIndex, unsigned char R, unsigned char G, unsigned char B) {
    // TODO
}

void initLedArrayPca9685(LedArray* ledArray, I2cBusConnection* i2cBusConnection) {
    initLedArray(ledArray, &ledArrayInitPca9685, &ledArrayWriteValuePca9685, (int*) i2cBusConnection);
}
