#ifndef I2C_SLAVE_INTERRUPT_PC_H
#define I2C_SLAVE_INTERRUPT_PC_H

#include <windows.h>

#include "../../../../common/i2c/i2cCommon.h"

/**
 * Callback function used to check if there is data transmitted from the master to the slave.
 */
DWORD WINAPI masterToSlaveCallback(LPVOID lpvParam);

/**
 * Callback function used to send from the slave to the master.
 */
DWORD WINAPI slaveToMasterCallback(LPVOID lpvParam);

/**
 * Function to call to handle the I2C (use Pipe) data from the master.
 */
void handleI2CDataFromMaster(I2cBusConnection* i2cBusConnection);

/**
* Function to call to send through the I2C (use Pipe) data from the slave to the master.
*/
void sendI2CDataToMaster(I2cBusConnection* i2cBusConnection);

#endif
