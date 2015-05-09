#ifndef SERIAL_PC_H
#define SERIAL_PC_H

#include <windows.h>

/**
 * Returns the Pipe Handle use to read data from a fake Serial Link.
 * @param serialPortIndex the serial Port Index for which we want the Input Pipe Handle
 * @return the HANDLE  use to read data from a fake Serial Link.
 */
HANDLE getSerialInputPipeHandle(unsigned char serialPortIndex);

#endif
