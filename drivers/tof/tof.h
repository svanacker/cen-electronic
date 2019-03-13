#ifndef TOF_H
#define TOF_H

#include <stdbool.h>

#include "../../common/2d/2d.h"

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
typedef unsigned int tofSensorGetDistanceMMFunction(TofSensor* tofSensor);

/**
* Defines the contract For one Tof Sensor.
*/
struct TofSensor {
    /** If we enabled it. If disable, we do not try to initialize it .*/
    bool enabled;
    /** If we must change the address of the TOF at startup .*/
    bool changeAddress;
    /** The function which must be used to init the tof Sensor */
    tofSensorInitFunction* tofSensorInit;
    /** The function which must be used to read the distance */
    tofSensorGetDistanceMMFunction* tofGetDistanceMM;
    /** Stored the value of the last call */
    unsigned int lastDistanceMM;
    /** Stored the threshold for which we would like that it raises a notification. */
    unsigned int thresholdDistanceMM;
    /** pointer on other object (useful for I2C Connection for example) .*/
    /** Store the angle in radian of the sensor compared to the robot. We use the same coordinates than for Robot. */
    float orientationRadian;
    /** Generic pointer for context use */
    int* object;
};

/**
 * Init a Tof Sensor
 */
void initTofSensor(TofSensor* tofSensor, 
                    tofSensorInitFunction* tofSensorInit,
                    tofSensorGetDistanceMMFunction* tofGetDistanceMM,
                    unsigned int thresholdDistanceMM,
                    float orientationRadian,
                    int* object);

// UTILS FUNCTION

bool tofComputeDetectedPointIfAny(TofSensor* tofSensor, Point* pointOfView, float pointOfViewAngleRadian, Point* pointToUpdateIfAny);

bool isTofSensorBackwardOriented(TofSensor* tofSensor);

#endif