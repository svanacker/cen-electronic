#include <peripheral/legacy/i2c_legacy.h>
#include <peripheral/i2c.h>

#include <stdbool.h>

#include "../../../../common/setup/32/clockConstants32.h"

#include "../i2cMasterSetup.h"

#include "../../../../common/commons.h"
#include "../../../../common/i2c/i2cCommon.h"
#include "../../../../common/i2c/32/i2cCommon32.h"
#include "../../../../common/i2c/master/i2cMaster.h"
#include "../../../../common/log/logger.h"
#include "../../../../common/log/logLevel.h"
#include "../../../../common/io/printWriter.h"
#include "../../../../common/io/binaryPrintWriter.h"

// TODO : initialized Flag must be defined in I2cBus structure
static bool initialized = false;

void i2cMasterInitialize(I2cBus* i2cBus) {
    // Avoid more than one initialization
    if (initialized) {
        appendString(getOutputStreamLogger(DEBUG), "I2C Master already initialized\n");
        return;
    }
    if (i2cBus == NULL) {
        OpenI2C1(
                 // Configure I2C for 7 bit address mode.
                 I2C_ON,
                 // 100khz for PIC32.
                 0xC6);
    }
    else {
        I2C_MODULE i2cModule = getI2C_MODULE(i2cBus->portIndex);
        I2CConfigure(i2cModule, I2C_ON);
        I2CSetFrequency(i2cModule, GetPeripheralClock(), 100000L);
    }

    WaitI2C(i2cBus);

    appendString(getOutputStreamLogger(DEBUG), "I2C Master CONF=");
    appendBinary16(getOutputStreamLogger(DEBUG), I2C_ON, 4);
    appendCRLF(getOutputStreamLogger(DEBUG));

    initialized = true;
}

void i2cMasterFinalize(I2cBus* i2cBus) {
    if (initialized) {
        initialized = false;
        portableCloseI2C(i2cBus);
    }
}