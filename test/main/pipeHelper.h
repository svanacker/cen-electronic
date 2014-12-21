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
 * Write a char into a windows Pipe.
 * @param c the char that we want to send
 * @return true if no error occured and bytes written count is egal to 1, false else
 */
bool writeCharToPipe(HANDLE pipe, char c);

#endif
