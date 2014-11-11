#ifndef SERIAL_INPUT_INTERRUPT_H
#define SERIAL_INPUT_INTERRUPT_H

#include "../commons.h"
#include "../../common/io/buffer.h"

/**
 * Init an inputStream arround serial with index "serialPortIndex".
 * @param buffer the pointer on buffer object to store input from serial
 * @param serialPortIndex the specific port index
 */
void initSerialInputBuffer(Buffer* buffer, int serialPortIndex);

/**
 * Debug Function which writes the content of each input Buffer to an outputStream.
 * @param outputStream the outputStream where we want to print the content of the buffer
 */
void printSerialInputBuffers(OutputStream* outputStream);

#endif
