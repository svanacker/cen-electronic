#ifndef TOF_LIST_H
#define TOF_LIST_H

#include <stdbool.h>

#include "../../common/io/outputStream.h"

#include "tof.h"

// Forward declaration
typedef struct TofSensorList TofSensorList;

/**
 * Define the specific function which must be used to debug the tofSensorList.
 */
typedef void tofSensorListDebugTableFunction(OutputStream* outputStream, TofSensorList* tofSensorList);

/**
 * The struct defining a list of Tof Sensors.
 */
struct TofSensorList {
    /** An array of pointer on tofSensor. */
    TofSensor(*tofSensorArray)[];
    /** the size of the list. */
    unsigned int size;
    /** For Debug purpose */
    tofSensorListDebugTableFunction* tofSensorListDebugTable;
};

/**
 * Initializes a list of Tof Sensor.
 * @param tofSensorArray the array presized with TofSensor
 * @param tofSensorListSize the size of the array of Tof Sensor
 */
void initTofSensorList(TofSensorList* tofSensorList,
                       TofSensor(*tofSensorArray)[],
                       unsigned int tofSensorListSize,
                       tofSensorListDebugTableFunction* tofSensorListDebugTable
);

/**
 * Get a tof Sensor by his index.
 * @param index the index of the tofSensor to get.
 * @return a tofSensor at the right index.
 */
TofSensor* getTofSensorByIndex(TofSensorList* tofSensorList, unsigned int index);

/**
 * Get the size of the tof Sensor List.
 * @return the size of the tof Sensor List.
 */
unsigned int getTofSensorListSize(TofSensorList* tofSensorList);

#endif
