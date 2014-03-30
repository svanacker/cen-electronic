#include <i2c.h>
#include <p30fxxxx.h>

#include "../../../common/error/error.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "i2cSlaveSetup.h"

bool initialized = FALSE;

void i2cSlaveInitialize(char writeAddress) {
    // Avoid more than one initialization
    if (initialized) {
        writeError(I2C_MASTER_ALREADY_INITIALIZED);
        return;
    }
    I2CCONbits.STREN = 1;
    // I2CCONbits.GCEN = 1;
    I2CCONbits.DISSLW = 1;
    I2CCONbits.SCLREL = 1;

    // 7-bit I2C slave address must be initialised here.
    // we shift because i2c address is shift to the right
    // to manage read and write address
    I2CADD = writeAddress >> 1;

    // Interruption on I2C Slave
    // -> Priority of I2C Slave interruption
    IPC3bits.SI2CIP = 1;
    // -> Enable I2C Slave interruption
    IEC0bits.SI2CIE = 1;
    // -> Enable Interruption Flag => See the same code in interruption
    IFS0bits.SI2CIF = 0;

    // Enable I2C
    I2CCONbits.I2CEN = 1;
}
