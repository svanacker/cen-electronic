#ifndef TOF_DEBUG_H
#define TOF_DEBUG_H

#include "tofList.h"

#include "../../common/io/outputStream.h"

unsigned int appendTofSensorTypeAsString(OutputStream* outputStream, enum TofSensorType tofSensorType);

unsigned int appendTofSensorTypeAsShortString(OutputStream* outputStream, enum TofSensorType tofSensorType);

unsigned int addTofSensorTypeTableData(OutputStream* outputStream, enum TofSensorType tofSensorType, int columnSize);

unsigned int addTofSensorTypeShortTableData(OutputStream* outputStream, enum TofSensorType tofSensorType, int columnSize);
/**
 * Print a list of tof Sensor.
 */
void printTofSensorTable(OutputStream* outputStream, TofSensorList* tofSensorList, Point* pointOfView, float pointOfViewAngleRadian);

#endif
