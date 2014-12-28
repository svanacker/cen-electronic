#ifndef DRIVER_H
#define DRIVER_H

#include <stdbool.h>

#include "../device/transmitMode.h"

/**
 * Initialization function of the driver.
 * @return true if the function initialization is ok, false else.
 */
typedef bool driverInitFunction(void);

/**
 * Driver shutting down function.
 */
typedef void driverShutDownFunction(void);

/**
 * Function for querying the error state of the driver
 * @retrue true is the driver is ok, false otherwise
 */
typedef bool driverIsOkFunction(void);

/**
 * Function for querying the name of the driver.
 * @return the name of the driver
 */
typedef const char* driverGetNameFunction(void);

/**
 * Descriptor of a driver.
 */
typedef struct {
    /** Callback to an init Function. */
    driverInitFunction *driverInit;
    /** Callback to a shutdown Function. */
    driverShutDownFunction *driverShutDown;
    /** Function to get the name of the function. */
    driverGetNameFunction *driverGetName;
    /** How we can communicate with the driver (Uart, I2C, local ...). */
	TransmitMode transmitMode;
} DriverDescriptor;

/**
 * Initializes the driver represented by the given descriptor.
 * @param driverDescriptor the descriptor of the driver.
 * @return true if the driver initialization is ok, false else
 */
bool driverInit(const DriverDescriptor *driverDescriptor);

/**
 * Shuts down the driver represented by the given descriptor.
 * @param driverDescriptor the descriptor of the driver.
 */
void driverShutDown(const DriverDescriptor *driverDescriptor);

#endif
