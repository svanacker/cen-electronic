#ifndef TOF_DEBUG_H
#define TOF_DEBUG_H

#include "tof.h"

#include "../../common/io/outputStream.h"

// TYPE

unsigned int appendTofSensorTypeAsString(OutputStream* outputStream, enum TofSensorType tofSensorType);

unsigned int addTofSensorTypeTableData(OutputStream* outputStream, enum TofSensorType tofSensorType, int columnSize);

// USAGE TYPE

unsigned int appendTofSensorUsageTypeAsString(OutputStream* outputStream, enum TofSensorUsageType tofSensorUsageType);

unsigned int appendTofSensorUsageTypeAsShortString(OutputStream* outputStream, enum TofSensorUsageType tofSensorUsageType);

unsigned int addTofSensorUsageTypeTableData(OutputStream* outputStream, enum TofSensorUsageType tofSensorUsageType, int columnSize);

unsigned int addTofSensorUsageTypeShortTableData(OutputStream* outputStream, enum TofSensorUsageType tofSensorUsageType, int columnSize);

#endif
