#ifndef CODERS_DEBUG_H
#define CODERS_DEBUG_H

#include "coders.h"

#include "../../common/io/outputStream.h"

void printCoderTable(OutputStream* outputStream);

void enableCoderDebug(unsigned int coderDebugIterationCountParam, unsigned int durationInDeciSec);

#endif
