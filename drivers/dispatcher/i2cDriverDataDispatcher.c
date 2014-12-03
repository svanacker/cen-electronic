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

DriverDataDispatcher* addI2CDriverDataDispatcher(
        char* dispatcherName,
        Buffer* i2cMasterInputBuffer,
        char (*i2cMasterInputBufferArray)[],
        unsigned char i2cMasterInputBufferLength,
        OutputStream* i2cMasterOutputStream,
        InputStream* i2cMasterInputStream,
        int i2cAddress) {


    // Init the output Stream : I2C Master -> I2C Slave(address)
    initBuffer(&i2cTempBuffer, &i2cTempBufferArray, I2C_DRIVER_DATA_DISPATCHER_BUFFER_LENGTH, "I2C Master Output", "global");
    initMasterI2cOutputStream(i2cMasterOutputStream, &i2cTempBuffer, i2cAddress);

    // Init the input Stream : I2C Slave (address) -> I2C Master
    initBuffer(i2cMasterInputBuffer, i2cMasterInputBufferArray, i2cMasterInputBufferLength, "I2C Master Input", dispatcherName);
    initMasterI2cInputStream(i2cMasterInputBuffer, i2cMasterInputStream, i2cAddress);

    // Clear previous data to avoid buffer from the other board provided by error at the initialization
    // TODO : Clarify this, to avoid to read some bad data until we are ready !
    clearInputStream(i2cMasterInputStream);

    DriverDataDispatcher* result = addDriverDataDispatcher(
                                        TRANSMIT_I2C,
                                        dispatcherName,
                                        NULL,
                                        i2cAddress,
                                        i2cMasterInputStream,
                                        i2cMasterOutputStream,
                                        remoteDriverDataDispatcherTransmit
                                    );
    return result;
}

