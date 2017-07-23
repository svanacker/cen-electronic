#ifndef SERIAL_INPUT_INTERRUPT_H
#define SERIAL_INPUT_INTERRUPT_H

#include "serial.h"
#include "../../common/io/buffer.h"
#include "../../common/io/outputStream.h"

/**
 * Initializes an inputStream around serial with index "serialPortIndex".
 * @param buffer the pointer on buffer object to store input from serial
 * @param serialPort the specific port index
 */
void initSerialInputBuffer(Buffer* buffer, enum SerialPort serialPort);

#endif
