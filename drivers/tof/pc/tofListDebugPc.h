#ifndef TOF_LIST_DEBUG_PC_H
#define TOF_LIST_DEBUG_PC_H

#include "../../../drivers/tof/tof.h"
#include "../../../drivers/tof/tofList.h"
#include "../../../drivers/tof/tofListDebug.h"

#include "../../../common/2d/2d.h"

#include "../../../common/io/outputStream.h"

/**
 * Print a list of tof Sensor (PC Simulation).
 */
void printTofSensorDetectionTablePc(OutputStream* outputStream,
        TofSensorList* tofSensorList,
        Point* pointOfView,
        float pointOfViewAngleRadian);

/**
 * Print the Config Table (PC Simulation).
 */
void printTofSensorConfigTablePc(OutputStream* outputStream, TofSensorList* tofSensorList);

/**
 * Print the Network Table (PC Simulation).
 */
void printTofSensorNetworkTablePc(OutputStream* outputStream, TofSensorList* tofSensorList);


#endif

