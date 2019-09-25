#ifndef PATH_LIST_DEBUG_H
#define PATH_LIST_DEBUG_H

#include "../common/io/outputStream.h"

#include "pathList.h"

/**
* Print the list of path as table.
*/
void printPathListTable(OutputStream* outputStream, PathList* pathList);

// TESTS DATA

void addPathListTestsData(PathList* pathList, LocationList* locationList);

#endif
