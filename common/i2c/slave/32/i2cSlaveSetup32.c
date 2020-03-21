#include <stdbool.h>

#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#include <plib.h>

#include "../../../../common/setup/32/clockConstants32.h"

#include "../../../../common/error/error.h"
#include "../../../../common/i2c/i2cCommon.h"
#include "../../../../common/i2c/32/i2cCommon32.h"

#include "../../../../common/io/printWriter.h"
#include "../../../../common/io/binaryPrintWriter.h"

#include "../../../../common/log/logger.h"
#include "../../../../common/log/logLevel.h"

#include "../i2cSlaveSetup.h"

#define I2C_FREQUENCY       100000L

#define BRG_VAL     ((FOSC / 2 / I2C_FREQUENCY)-2)

void i2cSlaveInitialize(I2cBusConnection* i2cBusConnection) {

    // Avoid more than one initialization
    if (i2cBusConnection->opened) {
        writeError(I2C_SLAVE_ALREADY_INITIALIZED);
        return;
    }
    i2cBusConnection->opened = true;

    appendString(getDebugOutputStreamLogger(), "I2C Slave Write Address=");
    appendHex2(getDebugOutputStreamLogger(), i2cBusConnection->i2cAddress);
    appendCRLF(getDebugOutputStreamLogger());

    if (i2cBusConnection == NULL) {

        // Enable the I2C module with clock stretching enabled
        OpenI2C1(I2C_ON | I2C_7BIT_ADD | I2C_STR_EN, BRG_VAL);

        // 7-bit I2C slave address must be initialised here.
        // we shift because i2c address is shift to the right
        // to manage read and write address
        I2C1ADD = i2cBusConnection->i2cAddress >> 1;
        I2C1MSK = 0;

        // Interruption on I2C Slave
        // -> Priority of I2C Slave interruption
        mI2C1SetIntPriority(I2C_INT_PRI_3 | I2C_INT_SLAVE);
        // -> Enable Interruption Flag => See the same code in interruption
        mI2C1SClearIntFlag();

        // Enable I2C (MACRO)
        EnableIntSI2C1;
    } else {
        I2cBus* i2cBus = i2cBusConnection->i2cBus;
        I2C_MODULE i2cModule = getI2C_MODULE(i2cBus->port);
        I2CConfigure(i2cModule, I2C_ON | I2C_7BIT_ADD | I2C_STR_EN);
        I2CSetFrequency(i2cModule, GetPeripheralClock(), I2C_FREQUENCY);
        I2CSetSlaveAddress(i2cModule, i2cBusConnection->i2cAddress >> 1, 0, I2C_USE_7BIT_ADDRESS);

        INTClearFlag(INT_SOURCE_I2C_SLAVE(INT_I2C1));
        INTSetVectorPriority(INT_VECTOR_I2C(I2C1), INT_PRIORITY_LEVEL_3);
        INTSetVectorSubPriority(INT_VECTOR_I2C(I2C1), INT_SUB_PRIORITY_LEVEL_0);
        INTEnable(INT_SOURCE_I2C_SLAVE(I2C1), INT_ENABLED);
    }
}
