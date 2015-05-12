#include "i2cCommon.h"

#include <stdlib.h>

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/binaryPrintWriter.h"

/**
 * Check if the I2C Bus is not null
 * @return true if it's ok, false else
 */
bool checkI2cBusNotNull(I2cBus* i2cBus) {
    if (i2cBus == NULL) {
        writeError(I2C_BUS_NULL);
        return false;
    }
    return true;
}

/**
 * Check if the I2C Bus Connection is not null
 * @return true if it's ok, false else
 */
bool checkI2cBusConnectionNotNull(I2cBusConnection* i2cBusConnection) {
    if (i2cBusConnection == NULL) {
        writeError(I2C_BUS_CONNECTION_NULL);
        return false;
    }
    return true;
}

/**
 * Check if the I2C Bus has all information
 * @return true if everything is ok, false else
 */
bool checkI2cBus(I2cBus* i2cBus) {
    if (i2cBus->busType == I2C_BUS_TYPE_UNKNOWN) {
        writeError(I2C_BUS_TYPE_NOT_DEFINED);
        return false;
    }
    if (i2cBus->port == I2C_BUS_PORT_UNKOWN) {
        writeError(I2C_BUS_PORT_NOT_DEFINED);
        return false;
    }
    return true;
}

void initI2cBus(I2cBus* i2cBus, enum I2cBusType i2cBusType, enum I2cPort i2cPort) {
    if (!checkI2cBusNotNull(i2cBus)) {
        return;
    }
    i2cBus->busType = i2cBusType;
    i2cBus->port = i2cPort;
    checkI2cBus(i2cBus);
}

void initI2cBusConnection(I2cBusConnection* i2cBusConnection, I2cBus* i2cBus, unsigned char slaveAddress) {
    if (!checkI2cBusConnectionNotNull(i2cBusConnection)) {
        return;
    }
    if (!checkI2cBusNotNull(i2cBus)) {
        return;
    }
    checkI2cBus(i2cBus);

    i2cBusConnection->i2cBus = i2cBus;
    i2cBusConnection->i2cAddress = slaveAddress;
}

void printI2cBus(OutputStream* outputStream, I2cBus* i2cBus) {
    if (!checkI2cBusNotNull(i2cBus)) {
        return;
    }

    // Type
    appendString(outputStream, "I2C : type=");
    if (i2cBus->busType == I2C_BUS_TYPE_UNKNOWN) {
        appendString(outputStream, " !! UNKNOWN !!");    
    }
    if (i2cBus->busType == I2C_BUS_TYPE_MASTER) {
        appendString(outputStream, "MASTER");    
    }
    else if (i2cBus->busType == I2C_BUS_TYPE_MASTER) {
        appendString(outputStream, "SLAVE"); 
    }
    else {
        appendString(outputStream, "??");
    }

    // PortIndex
    appendStringAndDec(outputStream, ", portIndex=I2C_BUS_PORT_", i2cBus->port);

    // Config
    appendString(outputStream, ", CONF=");
    appendBinary16(outputStream, i2cBus->config, 4);
}

void printI2cBusConnection(OutputStream* outputStream, I2cBusConnection* i2cBusConnection) {
    if (!checkI2cBusConnectionNotNull(i2cBusConnection)) {
        return;
    }

    // Address
    appendStringAndDec(outputStream, "I2cBusConnection : i2cAddress=", i2cBusConnection->i2cAddress);
    appendString(outputStream, ", opened=");

    // Opened
    appendBool(outputStream, i2cBusConnection->opened);
}
