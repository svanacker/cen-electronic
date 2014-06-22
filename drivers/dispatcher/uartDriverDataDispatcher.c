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

void addUartDriverDataDispatcher(DriverDataDispatcher* uartDispatcher,
        char* dispatcherName,

        Buffer* uartInputBuffer,
		char (*uartInputBufferArray)[],
		unsigned char uartInputBufferLength,

        OutputStream* uartOutputStream,
        InputStream* uartInputStream,
		unsigned int targetUartIndex) {
    // Configure i2c Dispatcher
    uartDispatcher->transmitMode = TRANSMIT_UART;
    uartDispatcher->name = dispatcherName;
    uartDispatcher->address = targetUartIndex;
    uartDispatcher->driverDataDispatcherTransmitData = remoteDriverDataDispatcherTransmit;

    // Init the output Stream : Uart Buffer -> Slave/Target UARTxx
    initSerialOutputStream(uartOutputStream, targetUartIndex);
    uartDispatcher->outputStream = uartOutputStream;

    // Init the input Stream : Slave/Target UARTxx -> Uart Buffer
    initBuffer(uartInputBuffer, uartInputBufferArray, uartInputBufferLength, "UART Input", dispatcherName);
    initSerialInputBuffer(uartInputBuffer, targetUartIndex);
    uartDispatcher->inputStream = &(uartInputBuffer->inputStream);

    // add to the list
    addDriverDataDispatcher(uartDispatcher);

    // Clear previous data to avoid buffer from the other board
    clearInputStream(uartDispatcher->inputStream);
}
