#ifndef PCA9685_DEBUG_H
#define PCA9685_DEBUG_H

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cCommon.h"

#include "../../common/io/outputStream.h"

#include <stdbool.h>

/**
 * Test of all pwm.
 */
void pca9685_test(I2cBusConnection* i2cBusConnection);

// DEBUG

void pca9685_debugMainRegisterList(OutputStream* outputStream, I2cBusConnection* i2cBusConnection);

#endif
