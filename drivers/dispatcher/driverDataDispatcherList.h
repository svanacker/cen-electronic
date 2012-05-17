#ifndef DRIVER_DATA_DISPATCHER_LIST_H
#define DRIVER_DATA_DISPATCHER_LIST_H

#define MAX_DRIVER_DATA_DISPATCHER 5

#include "driverDataDispatcher.h"

/**
 * Tre struct defining a list of driver Data dispatcher.
 */
typedef struct {
    /** An array of pointer on driver Descriptor. */
    DriverDataDispatcher * dispatchers[MAX_DRIVER_DATA_DISPATCHER];
    /** the size of the list. */
    unsigned char size;
} DriverDataDispatcherList;

/**
 * Return the dispatcher list.
 */
DriverDataDispatcherList* getDispatcherList();

/**
 * Add a driver data dispatcher to the list.
 */
void addDriverDataDispatcher(DriverDataDispatcher* dispatcher);

/**
 * Get a driver data dispatcher by his index.
 */
DriverDataDispatcher* getDriverDataDispatcherByIndex(int index);

/**
 * Find a driver data dispatcher by transmit mode and address.
 */
DriverDataDispatcher* getDriverDataDispatcherByTransmitMode(int transmitMode, int address);

/**
 * Get the size of the driver data dispatcher list.
 */
int getDriverDataDispatcherCount();

/**
 * Init the dispatcher list.
 */
void initDriverDataDispatcherList();

/**
 * Handle data from all dispatcher list with a particular transmit Mode.
 * @return TRUE if data notification was handled
 */
BOOL handleNotificationFromDispatcherList(int transmitMode);


#endif
