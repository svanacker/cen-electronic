#ifndef I2C_MASTER_SETUP_PC_H
#define I2C_MASTER_SETUP_PC_H

#include <Windows.h>

#include "../../../../common/i2c/i2cCommon.h"

/**
 * Extended information used by the Pc to manage a simulation of the i2cBus.
 */
typedef struct I2cMasterBusPc {
    // the master pipe Handle.
    HANDLE masterPipeHandle;
    // the Slave pipe Handle
    HANDLE slavePipeHandle;
} I2cMasterBusPc;

/**
 * Returns the extended information used by the Pc to manage a simulation of the i2cBus.
 */
I2cMasterBusPc* getMasterI2cBusPc(I2cBus* i2cBus);

#endif
