#ifndef I2C_MASTER_SETUP_PC_H
#define I2C_MASTER_SETUP_PC_H

#include <Windows.h>

/**
* Returns the master pipe Handle.
* @return the pipe Handle, null if it was not yet initialized.
*/
HANDLE getMasterPipeHandle();

#endif
