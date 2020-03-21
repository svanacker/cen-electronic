#ifndef I2C_DRIVER_DATA_DISPATCHER_H
#define I2C_DRIVER_DATA_DISPATCHER_H

#include "driverDataDispatcher.h"
#include "driverDataDispatcherList.h"

#include "../../common/i2c/i2cCommon.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"

#define I2C_DRIVER_DATA_DISPATCHER_BUFFER_LENGTH    200

/**
 * Add the i2c driver data dispatcher to the list.
 * @param dispatcherName name of the dispatcher
 * @param i2cMasterInputBuffer the buffer which is used to store information which will send to the I2C Slave
 * @param i2cMasterInputBufferArray the underlying array for the i2cMasterInputBuffer
 * @param i2cMasterInputBufferLength the length of the i2cMasterInputBufferLength
 * @param i2cMasterOutputStream the stream which is used to manage the output of the I2C Master (I2C Master -> I2C Slave(address))
 * @param i2cMasterInputStream the stream which is used to manage the input of the I2C Master (I2C Slave (address) -> I2C Master)
 * @param i2cBusConnection a pointer on the i2c Bus (to manage more than one i2cBus, and to manage several target)
 * @return the created structure to store information about dispatcher
 */
DriverDataDispatcher* addI2CDriverDataDispatcher(
        const char* dispatcherName,
        Buffer* i2cMasterInputBuffer,
        unsigned char (*i2cMasterInputBufferArray)[],
        unsigned char i2cMasterInputBufferLength,
        OutputStream* i2cMasterOutputStream,
        InputStream* i2cMasterInputStream,
        I2cBusConnection* I2cBusConnection);

#endif

