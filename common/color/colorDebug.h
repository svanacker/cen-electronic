#ifndef COLOR_DEBUG_H
#define COLOR_DEBUG_H

#include <stdbool.h>

#include "color.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

/**
* Print the value of the color to the outputStream.
*/
void printColorType(OutputStream* outputStream, enum ColorType colorType);

#endif