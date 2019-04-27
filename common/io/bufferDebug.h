#ifndef BUFFER_DEBUG_H
#define BUFFER_DEBUG_H

#include "outputStream.h"
#include "buffer.h"

/**
 * Print the buffer in a debug mode, with all variables.
 * @param outputStream the output stream (often debug) where we writes some values
 * @param buffer the buffer (simulates object programming)
 * @throws IO_BUFFER_NULL if the pointer is NULL 
 */
void printDebugBuffer(OutputStream* outputStream, Buffer* buffer);

#endif

