#include <stdbool.h>

#include "../i2cMasterSetup.h"

#include "../../../../common/i2c/i2cCommon.h"
#include "../../../../common/i2c/master/i2cMaster.h"

#include "../../../../common/log/logger.h"
#include "../../../../common/log/logLevel.h"
#include "../../../../common/io/printWriter.h"

static bool initialized = false;

void i2cMasterInitialize(void) {
    // Avoid more than one initialization
    if (initialized) {
        appendString(getOutputStreamLogger(DEBUG), "I2C PC Master already initialized\n");
        return;
    }
    initialized = true;
}

void i2cMasterFinalize(void) {
    if (initialized) {
        initialized = false;
        portableCloseI2C();
    }
}
