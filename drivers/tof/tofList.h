#ifndef TOF_LIST_H
#define TOF_LIST_H

#include <stdbool.h>

#include "../../common/2d/2d.h"

#include "../../common/io/outputStream.h"

#include "tof.h"
#include "../../drivers/ioExpander/ioExpander.h"
#include "../../drivers/i2c/multiplexer/multiplexerList.h"


// Forward declaration
typedef struct TofSensorList TofSensorList;

/**
* Define the specific function which must be used to see the configuration of the tof
* (but excluding the distance detection & the network).
*/
typedef void TofSensorListConfigTableDebugFunction(OutputStream* outputStream, TofSensorList* tofSensorList);

/**
* Define the specific function which must be used to see the network 
* (but excluding the distance detection & the config).
*/
typedef void TofSensorListNetworkTableDebugFunction(OutputStream* outputStream, TofSensorList* tofSensorList);

/**
 * Define the specific function which must be used to debug the tofSensorList in terms of 
 * detection
 */
typedef void TofSensorListDetectionTableDebugFunction(OutputStream* outputStream,
                                                      TofSensorList* tofSensorList,
                                                      Point* pointOfView, 
                                                      float pointOfViewAngleRadian);

/**
 * The struct defining a list of Tof Sensors.
 */
struct TofSensorList {
    /** An array of pointer on tofSensor. */
    TofSensor(*tofSensorArray)[];
    /** The Multiplexer List */
    MultiplexerList* multiplexerList;
    /** the size of the list. */
    unsigned int size;

    // BEEP MANAGEMENT
    /** The IO Expander used to beep */
    IOExpander* beepIoExpander;
    /** The ground io pin used to beep */
    unsigned int groundBeepIoPin;
    /** The +5V io pin used to beep */
    unsigned int vccBeepIoPin;
    /** To know the value of beep, we don't want to invoke too frequently the IOExpander to send the same value */
    bool beepValue;

    // IMPLEMENTATION CALLBACK
    /** If Debug Mode is activated .*/
    bool debug;
    /** To Debug the configuration of the sensor (distance, threshold, angles ...) */
    TofSensorListConfigTableDebugFunction* tofSensorListConfigTableDebug;
    /** To Debug the network of the sensor (i2c adress, multiplexer ...) */
    TofSensorListNetworkTableDebugFunction* tofSensorListNetworkTableDebug;
    /** To Debug the detection part of the sensor (call to the getDistance function which could raise an error). */
    TofSensorListDetectionTableDebugFunction* tofSensorListDetectionTableDebug;
};

/**
 * Initializes a list of Tof Sensor.
 * @param tofSensorArray the array presized with TofSensor
 * @param tofSensorListSize the size of the array of Tof Sensor
 */
void initTofSensorList(TofSensorList* tofSensorList,
                       TofSensor(*tofSensorArray)[],
                       unsigned int tofSensorListSize,
                       MultiplexerList* multiplexerList,
                       bool debug,
                       bool enabledAllSensors,
                       bool changeAddressAllSensors,
                       TofSensorListConfigTableDebugFunction* tofSensorListConfigTableDebug,
                       TofSensorListNetworkTableDebugFunction* tofSensorListNetworkTableDebug,
                       TofSensorListDetectionTableDebugFunction* tofSensorListDetectionTableDebug
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

/**
* Activate or not the beep on tofSensorList.
*/
void tofSensorListBeep(TofSensorList* tofSensorList, bool beepValue);

/**
 * Reset for all tof Sensor List the detection counter.
 * @param tofSensorList
 */
void tofSensorListResetDetectionCount(TofSensorList* tofSensorList);

#endif
