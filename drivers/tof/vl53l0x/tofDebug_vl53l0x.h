#ifndef TOF_DEBUG_VL53L0X_H
#define TOF_DEBUG_VL53L0X_H

#include "../tofList.h"

#include <stdint.h>

#include "../../../common/2d/2d.h"

#include "../../../common/io/outputStream.h"

void printTofSensorConfigTableVL53L0X(OutputStream* outputStream, TofSensorList* tofSensorList);

void printTofSensorNetworkTableVL53L0X(OutputStream* outputStream, TofSensorList* tofSensorList);

/**
 * Print a list of tof Sensor VL53L0X (including the detection part but
 * excluding the config & the network.
 */
void printTofSensorDetectionTableVL53L0X(OutputStream* outputStream, TofSensorList* tofSensorList, Point* pointOfView, float pointOfViewAngleRadian);

#endif
