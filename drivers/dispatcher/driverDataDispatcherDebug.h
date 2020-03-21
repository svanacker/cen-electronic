#ifndef DRIVER_DATA_DISPATCHER_DEBUG_H
#define DRIVER_DATA_DISPATCHER_DEBUG_H

#include "../../common/io/outputStream.h"

#include "../../drivers/dispatcher/driverDataDispatcherList.h"

/**
 * Print the driver data dispatcher list.
 * @param outputStream the stream where we print the driverDataDispatherList
 * @param dispatcherList the dispatcherList that we want to print
 */
void printDriverDataDispatcherList(OutputStream* outputStream, DriverDataDispatcherList* dispatcherList);

#endif

