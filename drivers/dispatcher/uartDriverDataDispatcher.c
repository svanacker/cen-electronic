#include "stdlib.h"

#include "driverDataDispatcher.h"
#include "driverDataDispatcherList.h"
#include "uartDriverDataDispatcher.h"
#include "remoteDriverDataDispatcher.h"

// Device
#include "../../drivers/driver.h"

// I2C management
#include "../../common/i2c/master/i2cMaster.h"
#include "../../common/i2c/master/i2cMasterInputStream.h"
#include "../../common/i2c/master/i2cMasterOutputStream.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/stream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/serial/serialOutputStream.h"
#include "../../common/serial/serialInputInterrupt.h"

DriverDataDispatcher* addUartDriverDataDispatcher(
        char* dispatcherName,

        Buffer* uartInputBuffer,
        char (*uartInputBufferArray)[],
        unsigned char uartInputBufferLength,

        OutputStream* uartOutputStream,
        InputStream* uartInputStream,
        unsigned int targetUartIndex) {

    // Init the output Stream : Uart Buffer -> Slave/Target UARTxx
    initSerialOutputStream(uartOutputStream, targetUartIndex);

    // Init the input Stream : Slave/Target UARTxx -> Uart Buffer
    initBuffer(uartInputBuffer, uartInputBufferArray, uartInputBufferLength, "UART Input", dispatcherName);
    initSerialInputBuffer(uartInputBuffer, targetUartIndex); // TODO : TO Verify !!!


    DriverDataDispatcher* result = addDriverDataDispatcher(
                                        TRANSMIT_UART,
                                        dispatcherName,
                                        NULL,
                                        targetUartIndex,
                                        uartInputStream,
                                        uartOutputStream,
                                        remoteDriverDataDispatcherTransmit);

    // Clear previous data to avoid buffer from the other board
    // TODO : Check if we must to this at this time
    clearInputStream(result->inputStream);

    return result;
}
