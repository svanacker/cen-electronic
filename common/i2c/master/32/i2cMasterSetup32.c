#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#include <plib.h>

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

void i2cMasterInitialize(I2cBus* i2cBus) {
    OutputStream* outputStream = getDebugOutputStreamLogger();
    appendString(outputStream, "Initializing I2C ...");

    // Avoid more than one initialization
    if (i2cBus->initialized) {
        printI2cBus(outputStream, i2cBus);
        appendCRLF(outputStream);
        appendString(getDebugOutputStreamLogger(), "\n!!! ALREADY INITIALIZED !!!\n");
        return;
    }
    i2cBus->initialized = true;
    #define I2C_BRG     0xC6    // 100khz for PIC32
    // Configure I2C for 7 bit address mode
    #define I2C_CON     I2C_ON

    i2cBus->config = I2C_CON;

    if (i2cBus == NULL) {
        OpenI2C1(
                 // Configure I2C for 7 bit address mode.
                 I2C_CON,
                 // 100khz for PIC32.
                 I2C_BRG);
    }
    else {
        I2C_MODULE i2cModule = getI2C_MODULE(i2cBus->port);
        I2CConfigure(i2cModule, I2C_ON);
        I2CSetFrequency(i2cModule, GetPeripheralClock(), 100000L);
    }

    WaitI2C(i2cBus);
    
    // Indicates that it's ok !
    appendString(outputStream, "OK\n"); 
    printI2cBus(outputStream, i2cBus);
    appendCRLF(outputStream);
}

void i2cMasterFinalize(I2cBus* i2cBus) {
    if (i2cBus->initialized) {
        i2cBus->initialized = false;
        i2cBus->config = 0;
        i2cBus->port = I2C_BUS_TYPE_UNKNOWN;
        portableMasterCloseI2C(i2cBus);
    }
}