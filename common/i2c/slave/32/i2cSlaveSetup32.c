#include <stdbool.h>
#include <peripheral/i2c.h>

#include "../../../../common/error/error.h"

#include "../../../../common/io/printWriter.h"
#include "../../../../common/io/binaryPrintWriter.h"

#include "../../../../common/log/logger.h"
#include "../../../../common/log/logLevel.h"

#include "../i2cSlaveSetup.h"

#define I2C_FREQUENCY       100000L

#define BRG_VAL     ((FOSC / 2 / I2C_FREQUENCY)-2)

static bool initialized = false;
static unsigned char slaveWriteAddress;

unsigned char getI2cWriteAddress(void) {
    return slaveWriteAddress;
}

unsigned char getI2cReadAddress(void) {
    return slaveWriteAddress | 1;
}

void i2cSlaveInitialize(unsigned char writeAddress) {

    // Avoid more than one initialization
    if (initialized) {
        writeError(I2C_SLAVE_ALREADY_INITIALIZED);
        return;
    }
    slaveWriteAddress = writeAddress;
    initialized = true;
    
    appendString(getOutputStreamLogger(DEBUG), "I2C Slave Write Address=");
    appendHex2(getOutputStreamLogger(DEBUG), writeAddress);
    appendCRLF(getOutputStreamLogger(DEBUG));
    
    // Enable the I2C module with clock stretching enabled
    OpenI2C1(I2C_ON | I2C_7BIT_ADD | I2C_STR_EN, BRG_VAL);

    // 7-bit I2C slave address must be initialised here.
    // we shift because i2c address is shift to the right
    // to manage read and write address
    I2C1ADD = writeAddress >> 1;
    I2C1MSK = 0;

    // Interruption on I2C Slave
    // -> Priority of I2C Slave interruption
    mI2C1SetIntPriority(I2C_INT_PRI_3 | I2C_INT_SLAVE);
    // -> Enable Interruption Flag => See the same code in interruption
    mI2C1SClearIntFlag();

    // Enable I2C
    EnableIntSI2C1;
}
