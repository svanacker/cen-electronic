#ifndef END_MATCH_DEBUG_H
#define END_MATCH_DEBUG_H

#include "endMatch.h"

#include "../../common/io/outputStream.h"

/**
* Print a table to debug the end of Match structure.
* @param outputStream where we print the table
*/
void printEndOfMatchTable(OutputStream* outputStream, EndMatch* endMatch);

#endif

