#include "i2cBusConnectionList.h"

#include <stdlib.h>
#include <stdbool.h>

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logHandler.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/i2c/i2cCommon.h"

/** Singleton : list of I2cConnectionBus. */
static I2cBusConnectionList i2cBusConnectionList;

I2cBusConnectionList* getI2cBusConnectionList() {
    return &i2cBusConnectionList;
}

void initI2cBusConnectionList(I2cBusConnection(*i2cBusConnectionListArray)[], unsigned char i2cBusConnectionListSize) {
    if (i2cBusConnectionListArray == NULL) {
        writeError(I2C_BUS_CONNECTION_LIST_NOT_INITIALIZED);
    }
    i2cBusConnectionList.busConnectionArray = i2cBusConnectionListArray;
    i2cBusConnectionList.maxSize = i2cBusConnectionListSize;
    i2cBusConnectionList.size = 0;
}

I2cBusConnection* getI2cBusConnectionByIndex(int index) {
	if (i2cBusConnectionList.maxSize == 0) {
		writeError(I2C_BUS_CONNECTION_LIST_NOT_INITIALIZED);
		return NULL;
	}
	if (index < 0 || index >= i2cBusConnectionList.maxSize) {
		writeError(I2C_BUS_CONNECTION_LIST_ILLEGAL_INDEX);
		return NULL;
	}
	I2cBusConnection* result = (I2cBusConnection*)i2cBusConnectionList.busConnectionArray;
	// we don't need use sizeof because our pointer is a I2cBusConnection pointer, so the shift
	// is already of the structure, we just have to shift of index.
	result += index;

	return result;
}

I2cBusConnection* addI2cBusConnection(I2cBus* i2cBus, unsigned char i2cSlaveAddress, bool defaultInitConnection) {
    if (i2cBusConnectionList.busConnectionArray == NULL) {
        writeError(I2C_BUS_CONNECTION_LIST_NOT_INITIALIZED);
        return NULL;
    }
    unsigned char size = i2cBusConnectionList.size;
    if (size < i2cBusConnectionList.maxSize) {
        I2cBusConnection* result = getI2cBusConnectionByIndex(size);
        result->i2cAddress = i2cSlaveAddress;
        i2cBusConnectionList.size++;
        if (defaultInitConnection) {
            initI2cBusConnection(result, i2cBus, i2cSlaveAddress);
        }
        return result;
    } else {
        writeError(TOO_MUCH_I2C_BUS_CONNECTION);
        return NULL;
    }
}

I2cBusConnection* getOrCreateI2cBusConnection(I2cBus* i2cBus, unsigned char i2cSlaveAddress, bool defaultInitConnection) {
    int size = i2cBusConnectionList.size;
    int i;
    for (i = 0; i < size; i++) {
        I2cBusConnection* i2cBusConnection = getI2cBusConnectionByIndex(i);
        if (i2cBusConnection->i2cBus != i2cBus) {
            continue;
        }
        if (i2cBusConnection->i2cAddress == i2cSlaveAddress) {
            return i2cBusConnection;
        }
    }
    // If no Bus Connection was found, we add it !
    return addI2cBusConnection(i2cBus, i2cSlaveAddress, defaultInitConnection);
}

I2cBusConnection* getI2cBusConnectionBySlaveAddress(unsigned char slaveAddress) {
    int size = i2cBusConnectionList.size;
    int i;
    for (i = 0; i < size; i++) {
        I2cBusConnection* i2cBusConnection = getI2cBusConnectionByIndex(i);
        if (!i2cBusConnection->opened) {
            continue;
        }
        if (i2cBusConnection->i2cAddress == slaveAddress) {
            return i2cBusConnection;
        }
    }
    return NULL;
}

int getI2cBusConnectionListCount() {
    return i2cBusConnectionList.size;
}
