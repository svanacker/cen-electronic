#ifndef NULL_OUTPUT_STREAM_H
#define NULL_OUTPUT_STREAM_H

#include "outputStream.h"

/**
 * Init a null outputStream (equivalent to writing to dev/null on linux)
 * @param outputStream the C structure pointer (POO simulation).
 */
void initNullOutputStream(OutputStream* outputStream);

#endif
