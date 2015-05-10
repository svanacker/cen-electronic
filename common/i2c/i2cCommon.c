#include "i2cCommon.h"

#include <stdlib.h>

#include "../../common/error/error.h"

void initI2cBus(I2cBus* i2cBus, unsigned char portIndex) {
    if (portIndex == 0) {
        writeError(I2C_BUS_PORT_INDEX_NOT_DEFINED);
        return;
    }
    i2cBus->portIndex = portIndex;
}

void initI2cBusConnection(I2cBusConnection* i2cBusConnection, I2cBus* i2cBus, unsigned char slaveAddress) {
    if (i2cBus == NULL) {
        writeError(I2C_BUS_PORT_NULL);
        return;
    }
    if (i2cBus->portIndex == 0) {
        writeError(I2C_BUS_PORT_INDEX_NOT_DEFINED);
        return;
    }
    i2cBusConnection->i2cBus = i2cBus;
    i2cBusConnection->i2cAddress = slaveAddress;
}