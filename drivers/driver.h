#ifndef DRIVER_H
#define DRIVER_H

#include "../common/commons.h"
#include "../common/io/inputStream.h"
#include "../common/io/outputStream.h"

/**
 * Initialization function of the driver.
 */
typedef bool driverInitFunction(void);

/**
 * Driver shutting down function.
 */
typedef void driverShutDownFunction(void);

/**
 * Function for querying the error state of the driver
 * @retrue TRUE is the driver is ok, FALSE otherwise
 */
typedef bool driverIsOkFunction(void);

/**
 * Function for querying the name of the driver.
 */
typedef const char* driverGetNameFunction(void);

/**
 * Returns the transmit mode which must be used by the driver.
 * @param defaultTransmitMode the global transmit mode which will be used
 * by default
 */
typedef int driverGetTransmitModeFunction(int defaultTransmitMode);

/**
 * Descriptor of a driver.
 */
typedef struct {
    // bool driverEnabled;
    driverInitFunction *driverInit;
    driverShutDownFunction *driverShutDown;
    driverGetNameFunction *driverGetName;
    int transmitMode;

} DriverDescriptor;

/**
 * Initializes the driver represented by the given descriptor.
 * @param driverDescriptor the descriptor of the driver.
 * @param debug flag for enabling debugging
 */
bool driverInit(const DriverDescriptor *driverDescriptor);

/**
 * Shuts down the driver represented by the given descriptor.
 * @param driverDescriptor the descriptor of the driver.
 */
void driverShutDown(const DriverDescriptor *driverDescriptor);

#endif
