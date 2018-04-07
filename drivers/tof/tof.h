#ifndef TOF_H
#define TOF_H

#include <stdbool.h>

// Forward declaration
typedef struct TofSensor TofSensor;

/**
 * Type of function to initialize the Tof Sensor.
 * We need an ioExpander so that we could select the right tof Sensor
 */
typedef bool tofSensorInitFunction(TofSensor* TofSensor);

/**
 * Define the function which must be used to get the distance 
 */
typedef unsigned int tofSensorGetDistanceMMFunction(TofSensor* TofSensor);

/**
* Defines the contract For one Tof Sensor.
*/
struct TofSensor {
    /** The function which must be used to init the tof Sensor */
    tofSensorInitFunction* tofSensorInit;
    /** The function which must be used to read the distance */
    tofSensorGetDistanceMMFunction* tofGetDistanceMM;
    /** Stored the value of the last call */
    unsigned int lastDistanceMM;
    /** Stored the threshold for which we would like that it raises a notification. */
    unsigned thresholdDistanceMM;
    /** pointer on other object (useful for I2C Connection for example) .*/
    int* object;
};

/**
 * Init a Tof Sensor
 */
void initTofSensor(TofSensor* tofSensor, 
                    tofSensorInitFunction* tofSensorInit,
                    tofSensorGetDistanceMMFunction* tofGetDistanceMM,
                    unsigned int thresholdDistanceMM,
                    int* object);

#endif