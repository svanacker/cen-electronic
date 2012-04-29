#ifndef SYSTEM_DRIVER_H
#define SYSTEM_DRIVER_H

#include "../../common/io/OutputStream.h"
#include "../../drivers/dispatcher/DriverDataDispatcher.h"

/**
* PING a data dispatcher.
* @param dispacher the dispatcher that we want to PING
*/ 
BOOL pingDriverDataDispatcher(DriverDataDispatcher* dispatcher);

/**
* Ping all dispatcher.
* @param debugOutputStream the stream in which we writes the debug information
*/
void pingDriverDataDispatcherList(OutputStream* debugOutputStream);

#endif
