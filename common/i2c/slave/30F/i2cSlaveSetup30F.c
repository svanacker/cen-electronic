#include <i2c.h>
#include <stdbool.h>
#include <p30Fxxxx.h>

#include "../../../../common/i2c/i2cCommon.h"

#include "../../../../common/error/error.h"

#include "../../../../common/io/printWriter.h"
#include "../../../../common/io/binaryPrintWriter.h"
#include "../../../../common/log/logger.h"
#include "../../../../common/log/logLevel.h"

#include "../i2cSlaveSetup.h"

bool initialized = false;

void i2cSlaveInitialize(I2cBusConnection* i2cBusConnection) {
    // Avoid more than one initialization
    if (i2cBusConnection->opened) {
        writeError(I2C_SLAVE_ALREADY_INITIALIZED);
        return;
    }
    i2cBusConnection->opened = true;

    I2CCONbits.STREN = 1;
    // I2CCONbits.GCEN = 1;
    I2CCONbits.DISSLW = 1;
    I2CCONbits.SCLREL = 1;

    // 7-bit I2C slave address must be initialised here.
    // we shift because i2c address is shift to the right
    // to manage read and write address
    I2CADD = i2cBusConnection->i2cAddress >> 1;

    // Interruption on I2C Slave
    // -> Priority of I2C Slave interruption
    IPC3bits.SI2CIP = 1;
    // -> Enable I2C Slave interruption
    IEC0bits.SI2CIE = 1;
    // -> Enable Interruption Flag => See the same code in interruption
    IFS0bits.SI2CIF = 0;

    // Enable I2C
    I2CCONbits.I2CEN = 1;

    appendString(getDebugOutputStreamLogger(), "I2C Slave CONF=");
    appendBinary16(getDebugOutputStreamLogger(), I2CCON, 4);
    appendCRLF(getDebugOutputStreamLogger());

    appendString(getDebugOutputStreamLogger(), "I2C Slave Write Address=");
    appendHex2(getDebugOutputStreamLogger(), i2cBusConnection->i2cAddress);
    appendCRLF(getDebugOutputStreamLogger());
}
