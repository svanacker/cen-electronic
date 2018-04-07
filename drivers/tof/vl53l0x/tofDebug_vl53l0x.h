#ifndef TOF_DEBUG_VL53L0X_H
#define TOF_DEBUG_VL53L0X_H

#include "../tofList.h"

#include "../../common/io/outputStream.h"

/**
 * Print a list of tof Sensor VL53L0X.
 */
void printTofSensorTableVL53L0X(OutputStream* outputStream, TofSensorList* tofSensorList);

#endif
