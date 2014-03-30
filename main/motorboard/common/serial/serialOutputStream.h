#ifndef SERIAL_STREAM_H
#define SERIAL_STREAM_H

#include "../commons.h"
#include "../../common/io/buffer.h"

#include "../../common/serial/serialLink.h"

/**
 * Init an inputStream arround serial with index "serialPortIndex".
 */
void initSerialOutputStream(OutputStream* outputStream, int serialPortIndex);

#endif
