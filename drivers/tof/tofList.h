#ifndef TOF_LIST_H
#define TOF_LIST_H

#include <stdbool.h>

#include "../../common/2d/2d.h"

#include "../../common/io/outputStream.h"

#include "tof.h"
#include "../../drivers/ioExpander/ioExpander.h"

// Forward declaration
typedef struct TofSensorList TofSensorList;

/**
 * Define the specific function which must be used to debug the tofSensorList.
 */
typedef void tofSensorListDebugTableFunction(OutputStream* outputStream, TofSensorList* tofSensorList, Point* pointOfView, float pointOfViewAngleRadian);

/**
 * The struct defining a list of Tof Sensors.
 */
struct TofSensorList {
    /** An array of pointer on tofSensor. */
    TofSensor(*tofSensorArray)[];
    /** The IO Expander used to beep */
    IOExpander* beepIoExpander;
    /** the size of the list. */
    unsigned int size;
    /** If Debug Mode is activated .*/
    bool debug;
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
                       bool debug,
                       bool enabledAllSensors,
                       bool changeAddressAllSensors,
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

void tofSensorListBeepOn(TofSensorList* tofSensorList);

void tofSensorListBeepOff(TofSensorList* tofSensorList);

#endif
