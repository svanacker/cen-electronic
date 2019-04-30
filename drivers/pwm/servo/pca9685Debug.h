#ifndef PCA9685_DEBUG_H
#define PCA9685_DEBUG_H

#include "../../../common/i2c/i2cCommon.h"
#include "../../../common/io/outputStream.h"

#include <stdbool.h>

// DEBUG

void pca9685_debugMainRegisterList(OutputStream* outputStream, I2cBusConnection* i2cBusConnection);

#endif
