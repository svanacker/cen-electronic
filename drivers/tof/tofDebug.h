#ifndef TOF_DEBUG_H
#define TOF_DEBUG_H

#include "tof.h"

#include "../../common/io/outputStream.h"

unsigned int appendTofSensorUsageTypeAsString(OutputStream* outputStream, enum TofSensorUsageType tofSensorUsageType);

unsigned int appendTofSensorUsageTypeAsShortString(OutputStream* outputStream, enum TofSensorUsageType tofSensorUsageType);

unsigned int addTofSensorUsageTypeTableData(OutputStream* outputStream, enum TofSensorUsageType tofSensorUsageType, int columnSize);

unsigned int addTofSensorUsageTypeShortTableData(OutputStream* outputStream, enum TofSensorUsageType tofSensorUsageType, int columnSize);

#endif
