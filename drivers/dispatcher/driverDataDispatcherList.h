#ifndef DRIVER_DATA_DISPATCHER_LIST_H
#define DRIVER_DATA_DISPATCHER_LIST_H

#define MAX_DRIVER_DATA_DISPATCHER 5

#include "driverDataDispatcher.h"

/**
 * Tre struct defining a list of driver Data dispatcher.
 */
typedef struct {
    /** An array of pointer on driver Descriptor. */
    DriverDataDispatcher(*dispatchers)[];
    /** the size of the list. */
    unsigned char size;
    /** the max size of the list. */
    unsigned char maxSize;

} DriverDataDispatcherList;

/**
 * Initializes a list of DriverDataDispatcher.
 * @param 
 */
void initDriverDataDispatcherList(DriverDataDispatcher(*driverDataDispatcherListArray)[], unsigned char driverDataDispatcherListSize);

/**
 * Return the dispatcher list.
 * @return the dispatcher list.
 */
DriverDataDispatcherList* getDispatcherList();

/**
 * Add a driver data dispatcher to the list.
 * @param transmitMode The corresponding Transmit mode
 * @param name debug name
 * @param addressString the address as char (for zigbee for example)
 * @param address The address (only for remote transmitMode). In case of addressString, address contains a checksum of addressString.
 * @param inputStream TODO : Description (can be null)
 * @param outputStream TODO : Description (can be null)
 * @param driverDataDispatcherTransmitData the function which is able to transmit the data from the driver to the device
 * @return dispatcher the data dispatcher added to the list.
 */
DriverDataDispatcher* addDriverDataDispatcher(
						int transmitMode,
						char* name,
						char* addressString,
						int address,
						InputStream* inputStream,
						OutputStream* outputStream,
						driverDataDispatcherTransmitDataFunction* driverDataDispatcherTransmitData
);

/**
 * Get a driver data dispatcher by his index.
 * @param index the index of the driverDataDispatcher to get.
 */
DriverDataDispatcher* getDriverDataDispatcherByIndex(int index);

/**
 * Find the first driver data dispatcher by transmit mode and address.
 * @param transmitMode the transmit mode to filter
 * @param address the address of the DriverDataDispatcher (For example for I2C)
 */
DriverDataDispatcher* getDriverDataDispatcherByTransmitMode(int transmitMode, int address);

/**
 * Get the size of the driver data dispatcher list.
 * @return the size of the driver data dispatcher list.
 */
int getDriverDataDispatcherCount();

/**
 * Handle data from all dispatcher list with a particular transmit Mode.
 * @return true if data notification was handled
 */
bool handleNotificationFromDispatcherList(int transmitMode);


#endif
