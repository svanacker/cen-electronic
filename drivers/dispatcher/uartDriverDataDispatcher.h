#ifndef UART_DRIVER_DATA_DISPATCHER_H
#define UART_DRIVER_DATA_DISPATCHER_H

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"

#include "driverDataDispatcher.h"
#include "driverDataDispatcherList.h"

#define UART_DRIVER_DATA_DISPATCHER_BUFFER_LENGTH        40

/**
* Add the uart driver data dispatcher to the list
* 
* @param dispatcherName name of the dispatcher
* @param uartInputBuffer the buffer which is used to store information which will send to the Slave/Target UART.
* @param uartInputBufferArray the underlying array for the uartInputBuffer
* @param uartInputBufferLength the length of the uartInputBufferLength
* @param uartOutputStream the stream which is used to manage the output of the UART (UART Master Board -> UART Slave Board)
* @param uartInputStream the stream which is used to manage the input of the UART (UART Slave Board -> UART Master Board)
* @param targetUartIndex the uart Index that we use to communicate with the slave board.
* @return the structure to store information about dispatcher
*/
DriverDataDispatcher* addUartDriverDataDispatcher(
                            char* dispatcherName,
                    
                            Buffer* uartInputBuffer,
                            char (*uartInputBufferArray)[],
                            unsigned char uartInputBufferLength,
                    
                            OutputStream* uartOutputStream,
                            InputStream* uartInputStream,
                            unsigned int targetUartIndex);

#endif

