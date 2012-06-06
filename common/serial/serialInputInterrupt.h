#ifndef SERIAL_INPUT_INTERRUPT_H
#define SERIAL_INPUT_INTERRUPT_H

#include "../commons.h"
#include "../../common/io/buffer.h"

/**
 * Init an inputStream arround serial with index "serialPortIndex".
 */
void initSerialInputBuffer(Buffer* buffer, int serialPortIndex);

#endif
