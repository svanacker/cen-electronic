#include "stdlib.h"

#include "driverDataDispatcher.h"
#include "driverDataDispatcherList.h"
#include "i2cDriverDataDispatcher.h"
#include "remoteDriverDataDispatcher.h"

// Drivers
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

/**
 * The stream to send data through I2C
 */
// temp buffer, shared by every i2cDriverDataDispatcher
// useful only for copyInputToOutputStream !
static char i2cTempBufferArray[I2C_DRIVER_DATA_DISPATCHER_BUFFER_LENGTH];
static Buffer i2cTempBuffer;

void addI2CDriverDataDispatcher(DriverDataDispatcher* i2cDispatcher,
        char* dispatcherName,
        Buffer* i2cMasterInputBuffer,
        char (*i2cMasterInputBufferArray)[],
        unsigned char i2cMasterInputBufferLength,
        OutputStream* i2cMasterOutputStream,
        InputStream* i2cMasterInputStream,
        int i2cAddress) {
    // Configure i2c Dispatcher
    i2cDispatcher->transmitMode = TRANSMIT_I2C;
    i2cDispatcher->name = dispatcherName;
    i2cDispatcher->address = i2cAddress;
    i2cDispatcher->driverDataDispatcherTransmitData = remoteDriverDataDispatcherTransmit;

    // Init the output Stream : I2C Master -> I2C Slave(address)
    initBuffer(&i2cTempBuffer, &i2cTempBufferArray, I2C_DRIVER_DATA_DISPATCHER_BUFFER_LENGTH, "I2C Output", "global");
    initMasterI2cOutputStream(i2cMasterOutputStream, &i2cTempBuffer, i2cAddress);
    i2cDispatcher->outputStream = i2cMasterOutputStream;

    // Init the input Stream : I2C Slave (address) -> I2C Master
    initBuffer(i2cMasterInputBuffer, i2cMasterInputBufferArray, i2cMasterInputBufferLength, "I2C Input", dispatcherName);
    initMasterI2cInputStream(i2cMasterInputBuffer, i2cMasterInputStream, i2cAddress);
    i2cDispatcher->inputStream = i2cMasterInputStream;

    // add to the list
    addDriverDataDispatcher(i2cDispatcher);

    // Clear previous data to avoid buffer from the other board
    clearInputStream(i2cMasterInputStream);
}

