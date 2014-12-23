#ifndef I2C_MASTER_SETUP_PC_H
#define I2C_MASTER_SETUP_PC_H

#include <Windows.h>

/**
* Returns the master pipe Handle.
* @return the pipe Handle, null if it was not yet initialized.
*/
HANDLE getMasterPipeHandle();

/**
* Returns the Slave pipe Handle.
* @param writeAddress the I2C Write Address
* @return the slave pipe Handle, null if it was not yet initialized
*/
HANDLE getSlavePipeHandle(unsigned char writeAddress);

#endif
