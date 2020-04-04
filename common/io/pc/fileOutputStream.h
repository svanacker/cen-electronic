#ifndef FILE_OUTPUT_STREAM_H
#define FILE_OUTPUT_STREAM_H

#include "../../../common/io/outputStream.h"

/**
 * Init a file outputStream.
 * @param outputStream the C structure pointer (POO simulation).
 */
void initFileOutputStream(OutputStream* outputStream, char* fileName);

#endif
