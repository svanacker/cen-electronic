#ifndef PIPE_HELPER_H
#define PIPE_HELPER_H

#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>

/**
 * Init the master to Slave Pipe with a pipeName.
 * @param pipeName the name of the pipe
 * @return the handle of the pipe if it was successfully created, NULL else
 */
HANDLE initMasterToSlavePipe(LPCWSTR pipeName);

/**
 * Init the slave to master with a pipeName
 * @param pipeName the name of the pipe
 * @return the handle to the existing pipe which is opened.
 */
HANDLE initSlaveToMasterPipe(LPCWSTR pipeName);

/**
 * Write a char into a windows Pipe.
 * @param pipe the pipe in which we write
 * @param c the char that we want to send
 * @return true if no error occured and bytes written count is egal to 1, false else
 */
bool writeCharToPipe(HANDLE pipe, char c);

/**
 * Returns the char read from the Pipe, 0x00 if no data
 * @param pipe the pipe in which we read
 * @return the char read from the Pipe, 0x00 if no data.
 */
unsigned char readCharFromPipe(HANDLE pipe);

#endif
