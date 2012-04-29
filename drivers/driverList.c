#include "driverList.h"

#include "driver.h"

#include "../common/commons.h"
#include "../common/io/buffer.h"
#include "../common/io/inputStream.h"
#include "../common/io/outputStream.h"

/** Singleton. */

/**
 * Driver list.
 */
static DriverDescriptorList drivers;

// I/O for all drivers
static char driverRequestBufferArray[DRIVER_REQUEST_BUFFER_LENGTH];
static Buffer driverRequestBuffer;
static char driverResponseBufferArray[DRIVER_RESPONSE_BUFFER_LENGTH];
static Buffer driverResponseBuffer;

void addDriver(DriverDescriptor* driverDescriptor, int transmitMode) {
    driverDescriptor->transmitMode = transmitMode;
    unsigned char size = drivers.size;
    drivers.drivers[size] = driverDescriptor;
    drivers.size++;
}

DriverDescriptor* getDriver(int index) {
    return drivers.drivers[index];
}

int getDriverCount() {
    return drivers.size;
}

void initDrivers() {
    int size = drivers.size;
    int i;
    for (i = 0; i < size; i++) {
        DriverDescriptor* driverDescriptor = drivers.drivers[i];
        driverInit(driverDescriptor);
    }
    initBuffer(&driverRequestBuffer, &driverRequestBufferArray, DRIVER_REQUEST_BUFFER_LENGTH, "DRV_REQ_BUF", "");
    initBuffer(&driverResponseBuffer, &driverResponseBufferArray, DRIVER_RESPONSE_BUFFER_LENGTH, "DRV_RES_BUF", "");
}

Buffer* getDriverRequestBuffer() {
    return &driverRequestBuffer;
}

Buffer* getDriverResponseBuffer() {
    return &driverResponseBuffer;
}

OutputStream* getDriverRequestOutputStream() {
    OutputStream* result = getOutputStream(&driverRequestBuffer);
    return result;
}


InputStream* getDriverResponseInputStream() {
    InputStream* result = getInputStream(&driverResponseBuffer);
    return result;
}
