#ifndef CONSOLE_INPUT_STREAM_H
#define CONSOLE_INPUT_STREAM_H

#include "../../../common/io/inputStream.h"

/**
 * Init a console inputStream (to be able to reproduce on pc the same feature than on micro-controller)
 * @param inputStream the C structure pointer (POO simulation).
 */
void initConsoleInputStream(InputStream* inputStream);

#endif
