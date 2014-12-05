#ifndef CONSOLE_OUTPUT_STREAM_H
#define CONSOLE_OUTPUT_STREAM_H

#include "../../../common/io/outputStream.h"

/**
 * Init a console outputStream (to write on the console when we writes some unit test)
 * @param outputStream the C structure pointer (POO simulation).
 */
void initConsoleOutputStream(OutputStream* outputStream);

#endif
