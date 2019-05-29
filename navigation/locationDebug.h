#ifndef LOCATION_DEBUG_H
#define LOCATION_DEBUG_H

#include "../common/io/outputStream.h"

#include "location.h"

unsigned int appendLocationUsageTypeAsString(OutputStream* outputStream, enum LocationUsageType LocationUsageType);

unsigned int appendLocationUsageTypeAsShortString(OutputStream* outputStream, enum LocationUsageType LocationUsageType);

unsigned int addLocationUsageTypeTableData(OutputStream* outputStream, enum LocationUsageType LocationUsageType, int columnSize);

unsigned int addLocationUsageTypeShortTableData(OutputStream* outputStream, enum LocationUsageType LocationUsageType, int columnSize);

#endif

