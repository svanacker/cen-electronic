#ifndef I2C_SLAVE_SETUP_PC_H
#define I2C_SLAVE_SETUP_PC_H

#include <Windows.h>

/**
 * Return the Pipe Handle used by the Slave to read Data from the Master.
 * @return the Pipe Handle used by the Slave to read Data from the Master.
 */
HANDLE getI2CMasterToSlaveHandle();

HANDLE getI2CSlaveToMasterHandle();

#endif
