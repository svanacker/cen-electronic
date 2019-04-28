#include "driverList.h"
#include "driver.h"

#include "../common/error/error.h"

#include "../common/io/buffer.h"
#include "../common/io/inputStream.h"
#include "../common/io/outputStream.h"

/**
 * Driver list (singleton pattern).
 */
static DriverDescriptorList drivers;

// I/O for all drivers because we only bufferized what will be transmitted
static Buffer* driverRequestBuffer;
static Buffer* driverResponseBuffer;

void addDriver(DriverDescriptor* driverDescriptor, TransmitMode transmitMode) {
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

void initDrivers(Buffer *aDriverRequestBuffer, unsigned char (*driverRequestBufferArray)[] , unsigned int requestLength,
                 Buffer *aDriverResponseBuffer, unsigned char (*driverResponseBufferArray)[] , unsigned int responseLength) {
    driverRequestBuffer = aDriverRequestBuffer;
    driverResponseBuffer = aDriverResponseBuffer;

    initBuffer(driverRequestBuffer, driverRequestBufferArray, requestLength, "DRIVER_REQUEST_BUFFER", "");
    initBuffer(driverResponseBuffer, driverResponseBufferArray, responseLength, "DRIVER_RESPONSE_BUFFER", "");

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
