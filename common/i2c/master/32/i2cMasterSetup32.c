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
        appendString(getDebugOutputStreamLogger(), "I2C Master already initialized\n");
        return;
    }
    #define I2C_BRG     0xC6    // 100khz for PIC32
    // Configure I2C for 7 bit address mode
    #define I2C_CON     I2C_ON

    if (i2cBus == NULL) {
        OpenI2C1(
                 // Configure I2C for 7 bit address mode.
                 I2C_CON,
                 // 100khz for PIC32.
                 I2C_BRG);
    }
    else {
        I2C_MODULE i2cModule = getI2C_MODULE(i2cBus->portIndex);
        I2CConfigure(i2cModule, I2C_ON);
        I2CSetFrequency(i2cModule, GetPeripheralClock(), 100000L);
    }

    WaitI2C(i2cBus);

    appendString(getDebugOutputStreamLogger(), "I2C Master CONF=");
    appendBinary16(getDebugOutputStreamLogger(), I2C_CON, 4);
    appendCRLF(getDebugOutputStreamLogger());

    initialized = true;
}

void i2cMasterFinalize(I2cBus* i2cBus) {
    if (initialized) {
        initialized = false;
        portableMasterCloseI2C(i2cBus);
    }
}