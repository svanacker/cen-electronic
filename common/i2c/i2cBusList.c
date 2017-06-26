#include "i2cBusList.h"

#include <stdlib.h>
#include <stdbool.h>

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logHandler.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/i2c/i2cCommon.h"

/** Singleton : list of I2cBus. */
static I2cBusList i2cBusList;

I2cBusList* getI2cBusList() {
    return &i2cBusList;
}

void initI2cBusList(I2cBus(*i2cBusListArray)[], unsigned char i2cBusListSize) {
    if (i2cBusListArray == NULL) {
        writeError(I2C_BUS_LIST_NOT_INITIALIZED);
    }
    i2cBusList.busArray = i2cBusListArray;
    i2cBusList.maxSize = i2cBusListSize;
    i2cBusList.size = 0;
}

I2cBus* getI2cBusByIndex(int index) {
	if (i2cBusList.maxSize == 0) {
		writeError(I2C_BUS_LIST_NOT_INITIALIZED);
		return NULL;
	}
	if (index < 0 || index >= i2cBusList.maxSize) {
		writeError(I2C_BUS_LIST_ILLEGAL_INDEX);
		return NULL;
	}
	I2cBus* result = (I2cBus*)i2cBusList.busArray;
	// we don't need use sizeof because our pointer is a I2cBus pointer, so the shift
	// is already of the structure, we just have to shift of index.
	result += index;

	return result;
}

I2cBus* addI2cBus(enum I2cBusType i2cBusType, enum I2cPort i2cPort) {
    if (i2cBusList.busArray == NULL) {
        writeError(I2C_BUS_LIST_NOT_INITIALIZED);
        return NULL;
    }
    unsigned char size = i2cBusList.size;
    if (size < i2cBusList.maxSize) {
        I2cBus* result = getI2cBusByIndex(size);
		initI2cBus(result, i2cBusType, i2cPort);
        i2cBusList.size++;
        return result;
    } else {
        writeError(TOO_MUCH_I2C_BUS);
        return NULL;
    }
}

I2cBus* getI2cBusByPortType(enum I2cPort port) {
    int size = i2cBusList.size;
    int i;
    for (i = 0; i < size; i++) {
        I2cBus* i2cBus = getI2cBusByIndex(i);
        if (i2cBus->port == port) {
            return i2cBus;
        }
    }
    return NULL;
}

int getI2cBusListCount() {
    return i2cBusList.size;
}
