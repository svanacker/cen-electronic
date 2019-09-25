#ifndef UART_DRIVER_DATA_DISPATCHER_H
#define UART_DRIVER_DATA_DISPATCHER_H

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/streamLink.h"

#include "driverDataDispatcher.h"
#include "driverDataDispatcherList.h"

#define UART_DRIVER_DATA_DISPATCHER_BUFFER_LENGTH        4000

/**
* Add the uart driver data dispatcher to the list
* @param streamLink a stream Link which wraps the serial Link 
* @param dispatcherName name of the dispatcher
* @param targetUartIndex the uart Index that we use to communicate with the slave board.
* @return the structure to store information about dispatcher
*/
DriverDataDispatcher* addUartDriverDataDispatcher(
                            StreamLink* streamLink,
                            const char* dispatcherName,
                            unsigned int targetUartIndex);

#endif

