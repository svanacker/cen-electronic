#include <stdlib.h>
#include <stdbool.h>

#include "driverDataDispatcherList.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logHandler.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../device/transmitMode.h"

/** Singleton : list of data dispatcher. */
static DriverDataDispatcherList dispatcherList;

DriverDataDispatcherList* getDispatcherList() {
    return &dispatcherList;
}

void initDriverDataDispatcherList(DriverDataDispatcher(*driverDataDispatcherListArray)[], unsigned char driverDataDispatcherListSize) {
    if (driverDataDispatcherListArray == NULL) {
        writeError(DISPATCHERS_LIST_NOT_INITIALIZED);
    }
    dispatcherList.dispatchers = driverDataDispatcherListArray;
    dispatcherList.maxSize = driverDataDispatcherListSize;
    dispatcherList.size = 0;
}

DriverDataDispatcher* addDriverDataDispatcher(
							TransmitMode transmitMode,
                            char* name,
                            char* addressString,
                            int address,
                            InputStream* inputStream,
                            OutputStream* outputStream,
                            driverDataDispatcherTransmitDataFunction* driverDataDispatcherTransmitData) {
    if (dispatcherList.dispatchers == NULL) {
        writeError(DISPATCHERS_LIST_NOT_INITIALIZED);
        return NULL;
    }
    unsigned char size = dispatcherList.size;
    if (size < dispatcherList.maxSize) {
        DriverDataDispatcher* result = getDriverDataDispatcherByIndex(size);
        result->transmitMode = transmitMode;
        result->name = name;
        result->addressString = addressString;
        result->address = address;
        result->inputStream = inputStream;
        result->outputStream = outputStream;
        result->driverDataDispatcherTransmitData = driverDataDispatcherTransmitData;
        dispatcherList.size++;
        return result;
    } else {
        writeError(TOO_MUCH_DRIVER_DATA_DISPATCHER);
        return NULL;
    }
}

DriverDataDispatcher* getDriverDataDispatcherByIndex(int index) {
    // TODO : Check size
    DriverDataDispatcher* result = (DriverDataDispatcher*)dispatcherList.dispatchers;
    // we don't need use sizeof because our pointer is a DriverDataDispatcher* pointer, so the shift
    // is already of the structure, we just have to shift of index.
    result += index;

    return result;
}

DriverDataDispatcher* getDriverDataDispatcherByTransmitMode(TransmitMode transmitMode, int address) {
    int size = dispatcherList.size;
    int i;
    for (i = 0; i < size; i++) {
        DriverDataDispatcher* dispatcher = getDriverDataDispatcherByIndex(i);
        if (dispatcher->transmitMode == transmitMode && dispatcher->address == address) {
            return dispatcher;
        }
    }
    return NULL;
}

int getDriverDataDispatcherCount() {
    return dispatcherList.size;
}

bool handleNotificationFromDispatcherList(TransmitMode transmitMode) {
    bool result = false;
    int size = dispatcherList.size;
    int i;
    for (i = 0; i < size; i++) {
        DriverDataDispatcher* dispatcher = getDriverDataDispatcherByIndex(i);
        if (dispatcher->transmitMode != transmitMode) {
            continue;
        }
        if (handleNotificationFromDispatcher(dispatcher)) {
            result = true;
        }
    }
    return result;
}
