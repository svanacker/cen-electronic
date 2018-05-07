#ifndef TOF_DEBUG_H
#define TOF_DEBUG_H

#include "tofList.h"

#include "../../common/io/outputStream.h"

/**
 * Print a list of tof Sensor.
 */
void printTofSensorTable(OutputStream* outputStream, TofSensorList* tofSensorList, Point* pointOfView, float pointOfViewAngleRadian);

#endif
