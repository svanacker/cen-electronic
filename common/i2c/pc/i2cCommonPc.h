#ifndef I2C_COMMON_PC_H
#define I2C_COMMON_PC_H

#include <Windows.h>

#include "../i2cCommon.h"

/**
 * Define the extended structure which store the extra information/variable needed by
 * PC to establish a connection.
 */
typedef struct I2cBusConnectionPc {
    LPCWSTR i2cPipeMasterName;
    HANDLE masterToSlaveHandle;
    HANDLE masterToSlaveThreadHandle;
    DWORD masterToSlaveThreadId;

    LPCWSTR i2cPipeSlaveName;
    HANDLE slaveToMasterHandle;
    HANDLE slaveToMasterThreadHandle;
    DWORD slaveToMasterThreadId;
} I2cBusConnectionPc;

void initI2cBusConnectionPc(I2cBusConnection* i2cBusConnection, I2cBus* i2cBus, I2cBusConnectionPc* i2cBusConnectionPc, unsigned char slaveAddress, LPCWSTR i2cPipeMasterName, LPCWSTR i2cPipeSlaveName);

/**
 * Returns the extended structure which store the extra information/variable needed by
 * Pc to manage a simulation of I2cBus.
 */
I2cBusConnectionPc* getI2cBusConnectionPc(I2cBusConnection* i2cBusConnection);

#endif