#ifndef PIN_DEBUG_H
#define PIN_DEBUG_H

#include <stdbool.h>

#include "pin.h"
#include "../../common/io/outputStream.h"


/**
 * Print All Pin Values.
 * @param outputStream the stream in which we write all values
 */
void printAllPinValues(PinList* pinList, OutputStream* outputStream);

#endif
