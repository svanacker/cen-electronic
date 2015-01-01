#ifndef SYSTEM_DRIVER_H
#define SYSTEM_DRIVER_H

#include "../../common/io/outputStream.h"
#include "../../drivers/dispatcher/driverDataDispatcher.h"

/**
* PING a data dispatcher.
* @param dispatcher the dispatcher that we want to PING
*/ 
bool pingDriverDataDispatcher(DriverDataDispatcher* dispatcher);

/**
* Ping all dispatcher.
* @param debugOutputStream the stream in which we writes the debug information
*/
void pingDriverDataDispatcherList(OutputStream* debugOutputStream);

#endif
