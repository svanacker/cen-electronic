#ifndef START_MATCH_DEBUG_H
#define START_MATCH_DEBUG_H

#include "startMatch.h"

#include "../../common/io/outputStream.h"

/**
* Print a table to debug the start of Match structure.
* @param outputStream where we print the table
*/
void printStartMatchTable(OutputStream* outputStream, StartMatch* startMatch);

#endif

