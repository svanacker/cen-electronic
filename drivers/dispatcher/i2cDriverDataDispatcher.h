#ifndef I2C_DRIVER_DATA_DISPATCHER_H
#define I2C_DRIVER_DATA_DISPATCHER_H

#include "driverDataDispatcher.h"
#include "driverDataDispatcherList.h"

#define I2C_DRIVER_DATA_DISPATCHER_BUFFER_LENGTH	40

/**
* Add the i2c driver data dispatcher to the list
*/
void addI2CDriverDataDispatcher(DriverDataDispatcher* i2cDispatcher,
        char* dispatcherName,
        Buffer* i2cMasterInputBuffer,
		char (*i2cMasterInputBufferArray)[],
		unsigned char i2cMasterInputBufferLength,
        InputStream* i2cMasterInputStream,
        OutputStream* i2cMasterOutputStream,
        int i2cAddress);

#endif

