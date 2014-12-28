#ifndef DRIVER_LIST_H
#define DRIVER_LIST_H

#include "driver.h"
#include "../common/io/buffer.h"
#include "../common/io/inputStream.h"
#include "../common/io/outputStream.h"

/** The max limit of driver list. */
#define MAX_DRIVER 3

/**
 * Tre struct defining a list of drivers.
 */
typedef struct {
    /** An array of pointer on driver Descriptor. */
    DriverDescriptor* drivers[MAX_DRIVER];
    /** the size of the list. */
    unsigned char size;
} DriverDescriptorList;


/**
 * Add a driver Descriptor to the list.
 * @param driverDescriptor the driver descriptor to add
 */
void addDriver(DriverDescriptor* driverDescriptor, TransmitMode transmitMode);

/**
 * Get the driver descriptor of index.
 * @param index the index in the array of descriptors
 * @return the descriptor at the specified index
 */
DriverDescriptor* getDriver(int index);

/**
 * Get the count of driver.
 * @return the count of driver
 */
int getDriverCount();

/**
 * Init the driver descriptor list.
 */
void initDrivers(Buffer *driverRequestBuffer, char (*driverRequestBufferArray)[] , unsigned char requestLength,
                 Buffer *driverResponseBuffer, char (*driverResponseBufferArray)[] , unsigned char responseLength);

/**
 * Get an OutputStream to write argument and parameters
 * for the driver.
 */
OutputStream* getDriverRequestOutputStream();

/**
 * Get a InputStream for driver corresponding to the
 * result.
 */
InputStream* getDriverResponseInputStream();

/**
 * Get the buffer correspondings to the input of the driver.
 */
Buffer* getDriverRequestBuffer();

/**
 * Get the buffer correspondings to the output of the driver.
 */
Buffer* getDriverResponseBuffer();

#endif

