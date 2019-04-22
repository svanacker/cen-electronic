#ifndef NAVIGATION_DEBUG_H
#define NAVIGATION_DEBUG_H

#include "navigation.h"

#include "../common/io/outputStream.h"

/**
* Print the list of outgoing Path for each location.
*/
void printNavigationDebugLocationAndOutgoingPathListTable(OutputStream* outputStream, Navigation* navigation);

#endif
