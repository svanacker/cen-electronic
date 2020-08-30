#ifndef LOCATION_DEBUG_H
#define LOCATION_DEBUG_H

#include "../common/io/outputStream.h"

#include "location.h"

// USAGE TYPE

unsigned int appendLocationUsageTypeAsString(OutputStream* outputStream, enum LocationUsageType locationUsageType);

unsigned int appendLocationUsageTypeAsShortString(OutputStream* outputStream, enum LocationUsageType locationUsageType);

unsigned int addLocationUsageTypeTableData(OutputStream* outputStream, enum LocationUsageType locationUsageType, int columnSize);

unsigned int addLocationUsageTypeShortTableData(OutputStream* outputStream, enum LocationUsageType locationUsageType, int columnSize);

// ADJUST TYPE
unsigned int appendLocationAdjustTypeAsString(OutputStream* outputStream, enum LocationAdjustType locationAdjustType);

unsigned int appendLocationAdjustTypeAsShortString(OutputStream* outputStream, enum LocationAdjustType locationAdjustType);

unsigned int addLocationAdjustTypeTableData(OutputStream* outputStream, enum LocationAdjustType locationAdjustType, int columnSize);

unsigned int addLocationAdjustTypeShortTableData(OutputStream* outputStream, enum LocationAdjustType locationAdjustType, int columnSize);


#endif

