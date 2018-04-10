#ifndef IO_EXPANDER_DEBUG_H
#define IO_EXPANDER_DEBUG_H

#include "ioExpander.h"
#include "ioExpanderList.h"

#include "../../common/io/outputStream.h"

/**
 * Print a list of states of IO as a table.
 */
void printIOExpanderStatesTable(OutputStream* outputStream, IOExpanderList* ioExpanderList);

#endif
