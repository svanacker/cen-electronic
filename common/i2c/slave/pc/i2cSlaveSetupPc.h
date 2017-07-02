#ifndef I2C_SLAVE_SETUP_PC_H
#define I2C_SLAVE_SETUP_PC_H

#include <Windows.h>

#include "../../../../common/i2c/i2cCommon.h"

/**
 * Define the extended structure which store the extra information/variable needed by
 * PC.
 */
typedef struct I2cSlaveBusConnectionPc {
    HANDLE masterToSlaveHandle;
    HANDLE masterToSlaveThreadHandle;
    DWORD  masterToSlaveThreadId;

    HANDLE slaveToMasterHandle;
    HANDLE slaveToMasterThreadHandle;
    DWORD  slaveToMasterThreadId;
} I2cSlaveBusConnectionPc;

/**
 * Returns the extended structure which store the extra information/variable needed by
 * Pc to manage a simulation of I2cBus.
 */
I2cSlaveBusConnectionPc* getSlaveI2cBusConnectionPc(I2cBusConnection* i2cBusConnection);

#endif
