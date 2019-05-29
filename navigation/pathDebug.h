#ifndef PATH_DEBUG_H
#define PATH_DEBUG_H

#include "../common/io/outputStream.h"

#include "path.h"


unsigned int appendPathDataUsageTypeAsString(OutputStream* outputStream, enum PathDataUsageType pathDataUsageType);

unsigned int appendPathDataUsageTypeAsShortString(OutputStream* outputStream, enum PathDataUsageType pathDataUsageType);

unsigned int addPathDataUsageTypeTableData(OutputStream* outputStream, enum PathDataUsageType pathDataUsageType, int columnSize);

unsigned int addPathDataUsageTypeShortTableData(OutputStream* outputStream, enum PathDataUsageType pathDataUsageType, int columnSize);

#endif
