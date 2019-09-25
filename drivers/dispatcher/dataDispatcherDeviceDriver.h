#ifndef DATA_DISPATCHER_DEVICE_DRIVER_H
#define DATA_DISPATCHER_DEVICE_DRIVER_H

#include <stdbool.h>

#include "driverDataDispatcher.h"
#include "driverDataDispatcherList.h"

/**
 * Ping a specific driverDataDispatcher.
 * @param dispatcherIndex the driverDataDispatcher index (remote board) to ping (in the list of dataDispatcherList).
 * @return true if it has successfully ping the board, false else. The board can be the "localhost" board.
 */
bool pingDriverDataDispatcher(unsigned char dispatcherIndex);

/**
 * Ping all driverDataDispatchers.
 * @return true if it has successfully ping all the boards, false else.
 */
bool pingDriverDataDispatcherList();

#endif
