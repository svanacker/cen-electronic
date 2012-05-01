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
static Buffer* driverRequestBuffer;
static Buffer* driverResponseBuffer;

void addDriver(DriverDescriptor* driverDescriptor, int transmitMode) {
    unsigned char size = drivers.size;
	if (size < MAX_DRIVER) {
	    drivers.drivers[size] = driverDescriptor;
	    driverDescriptor->transmitMode = transmitMode;
	    drivers.size++;
	}
	else {
		writeError(TOO_MUCH_DRIVERS);
	}
}

DriverDescriptor* getDriver(int index) {
    return drivers.drivers[index];
}

int getDriverCount() {
    return drivers.size;
}

void initDrivers(Buffer *aDriverRequestBuffer, char (*driverRequestBufferArray)[] , unsigned char requestLength,
				 Buffer *aDriverResponseBuffer, char (*driverResponseBufferArray)[] , unsigned char responseLength) {
	driverRequestBuffer = aDriverRequestBuffer;
	driverResponseBuffer = aDriverResponseBuffer;

    initBuffer(driverRequestBuffer, driverRequestBufferArray, requestLength, "DRV_REQ_BUF", "");
    initBuffer(driverResponseBuffer, driverResponseBufferArray, responseLength, "DRV_RES_BUF", "");

    int size = drivers.size;
    int i;
    for (i = 0; i < size; i++) {
        DriverDescriptor* driverDescriptor = drivers.drivers[i];
        driverInit(driverDescriptor);
    }
}

Buffer* getDriverRequestBuffer() {
    return driverRequestBuffer;
}

Buffer* getDriverResponseBuffer() {
    return driverResponseBuffer;
}

OutputStream* getDriverRequestOutputStream() {
    OutputStream* result = getOutputStream(driverRequestBuffer);
    return result;
}

InputStream* getDriverResponseInputStream() {
    InputStream* result = getInputStream(driverResponseBuffer);
    return result;
}
