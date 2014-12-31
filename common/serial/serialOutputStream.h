#ifndef SERIAL_STREAM_H
#define SERIAL_STREAM_H

#include "../../common/io/outputStream.h"

/**
 * Init an outputStream around serial with index "serialPortIndex".
 * @param outputStream the pointer on the outputStream object which will manage the serial output stream
 * @param serialPortIndex the index of the serial Port (@see serial.h)
 */
void initSerialOutputStream(OutputStream* outputStream, int serialPortIndex);

#endif
