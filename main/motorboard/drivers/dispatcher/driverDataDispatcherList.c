#include <stdlib.h>

#include "driverDataDispatcherList.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logHandler.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

/** Singleton : list of data dispatcher. */
static DriverDataDispatcherList dispatcherList;

DriverDataDispatcherList* getDispatcherList() {
	return &dispatcherList;
}

void initDriverDataDispatcherList() {
    dispatcherList.size = 0;
}

void addDriverDataDispatcher(DriverDataDispatcher* dispatcher) {
    unsigned char size = dispatcherList.size;
    if (size < MAX_DRIVER_DATA_DISPATCHER) {
        dispatcherList.dispatchers[size] = dispatcher;
        dispatcherList.size++;
    } else {
        writeError(TOO_MUCH_DRIVER_DATA_DISPATCHER);
    }
}

DriverDataDispatcher* getDriverDataDispatcherByIndex(int index) {
    return dispatcherList.dispatchers[index];
}

DriverDataDispatcher* getDriverDataDispatcherByTransmitMode(int transmitMode, int address) {
    int size = dispatcherList.size;
    int i;
    for (i = 0; i < size; i++) {
        DriverDataDispatcher* dispatcher = dispatcherList.dispatchers[i];
        if (dispatcher->transmitMode == transmitMode && dispatcher->address == address) {
            return dispatcher;
        }
    }
    return NULL;
}

int getDriverDataDispatcherCount() {
    return dispatcherList.size;
}

bool handleNotificationFromDispatcherList(int transmitMode) {
	bool result = false;
    int size = dispatcherList.size;
    int i;
    for (i = 0; i < size; i++) {
        DriverDataDispatcher* dispatcher = dispatcherList.dispatchers[i];
        if (dispatcher->transmitMode != transmitMode) {
            continue;
        }
        if (handleNotificationFromDispatcher(dispatcher)) {
			result = true;
		}
    }
	return result;
}
