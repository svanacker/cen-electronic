#include "tofListDebugPc.h"

#include "../tofListDebug.h"

/**
 * Print the Config Table (PC Simulation)
 */
void printTofSensorConfigTablePc(OutputStream* outputStream, TofSensorList* tofSensorList) {
    printTofSensorConfigTable(outputStream, tofSensorList);
}

/**
 * Print the Network Table (PC Simulation)
 */
void printTofSensorNetworkTablePc(OutputStream* outputStream, TofSensorList* tofSensorList) {
    printTofSensorNetworkTable(outputStream, tofSensorList);
}

void printTofSensorDetectionTablePc(OutputStream* outputStream, TofSensorList* tofSensorList, Point* pointOfView, float pointOfViewAngleRadian) {
    printTofSensorDetectionTable(outputStream, tofSensorList, pointOfView, pointOfViewAngleRadian);
}

