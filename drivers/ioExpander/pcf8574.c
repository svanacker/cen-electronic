#include "pcf8574.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../../common/delay/cenDelay.h"

#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/master/i2cMaster.h"

#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#define PCF8574_IO_COUNT     ((unsigned int) 8)

// BASE FUNCTION

unsigned char isPCF8574Present(I2cBusConnection* i2cBusConnection) {
    unsigned char result;

    portableMasterWaitSendI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWaitSendI2C(i2cBusConnection);
    result = portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterStopI2C(i2cBusConnection);

    return result;
}

void writePCF8574(I2cBusConnection* i2cBusConnection, unsigned char outData) {
    portableMasterWaitSendI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress); // send write address
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, outData); // write new outputs to buffer
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, outData); // force data to output pins
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterStopI2C(i2cBusConnection);
}

unsigned char readPCF8574(I2cBusConnection* i2cBusConnection) {
    unsigned char result;
    portableMasterWaitSendI2C(i2cBusConnection);
    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    // send read address (bit zero is set)
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress | 1);
    WaitI2cBusConnection(i2cBusConnection);
    result = portableMasterReadI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterNackI2C(i2cBusConnection);
    portableMasterStopI2C(i2cBusConnection);

    return result;
}

