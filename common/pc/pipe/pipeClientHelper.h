#ifndef PIPE_CLIENT_HELPER_H
#define PIPE_CLIENT_HELPER_H

#include <stdio.h>
#include <Windows.h>

/**
 * Init the client pipe which will consume data from a server a pipeName
 * @param pipeName the name of the pipe
 * @return the handle to the existing pipe which is opened.
 */
HANDLE initClientPipe(LPCWSTR pipeName);

/**
 * Returns the char read from the Pipe, 0x00 if no data
 * @param pipe the pipe in which we read
 * @return the char read from the Pipe, 0x00 if no data.
 */
unsigned char readCharFromPipe(HANDLE pipe);

#endif
