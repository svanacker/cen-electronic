#ifndef MULTIPLEXER_DEBUG_H
#define MULTIPLEXER_DEBUG_H

#include "multiplexer.h"
#include "multiplexerList.h"

#include "../../../common/io/outputStream.h"

/**
 * Print a list of multiplexer as a table.
 */
void printMultiplexerTable(OutputStream* outputStream, MultiplexerList* multiplexerList);

#endif
