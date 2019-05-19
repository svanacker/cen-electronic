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
 * Type of TofSensor, someare used to detect collision, are used for actions
 */
enum TofSensorType {
    /** The type was not defined */
    TOF_SENSOR_TYPE_UNKNOWN = 0,
    /** The tof is used to detect Collision. */
    TOF_SENSOR_TYPE_COLLISION = 1,
    /** The tof is used to detect actions. */
    TOF_SENSOR_TYPE_ACTION = 2
};

/**
* Defines the contract For one Tof Sensor.
*/
struct TofSensor {
    /** An name for the sensor. */
    char* name;
    /** The type of Sensor. */
    enum TofSensorType type;
    /** If we enabled it. If disable, we do not try to initialize it .*/
    bool enabled;
    /** If we must change the address of the TOF at startup .*/
    bool changeAddress;
    /** True if we use a I2C Multiplexer */
    bool useMultiplexer;
    /** The address of the multiplexer. */
    unsigned char multiplexerAddress;
    /** The index of the multiplexer if we use it (0 to 7). */
    unsigned char multiplexerChannel;
    /** The function which must be used to init the tof Sensor */
    tofSensorInitFunction* tofSensorInit;
    /** The function which must be used to read the distance */
    tofSensorGetDistanceMMFunction* tofGetDistanceMM;
    /** Stored the value of the last call */
    unsigned int lastDistanceMM;
    /** Stored the threshold for which we would like that it raises a notification. */
    unsigned int thresholdDistanceMM;
    /** The threshold of how many detections must be done before we consider that the measure is valid */
    unsigned int detectionThreshold;
    /** The counter of how many detected were done. */
    unsigned int detectedCount;
    /** The beam angle of what he could detect. */
    float beamAngleRadian;
    /** pointer on other object (useful for I2C Connection for example) .*/
    /** Store the angle in radian of the sensor compared to the robot. We use the same coordinates than for Robot. */
    float orientationRadian;
    /** The distance between the Sensor compared and the center of the robot. */
    float distanceFromRobotCenter;
    /** The angle of the central point of the Sensor compared to the center of the robot (with X axis along the going point). */
    float angleFromRobotCenter;
    /** Generic pointer for context use */
    int* object;
};

/**
 * Init a Tof Sensor
 */
bool initTofSensor(TofSensor* tofSensor, 
                    tofSensorInitFunction* tofSensorInit,
                    tofSensorGetDistanceMMFunction* tofGetDistanceMM,
                    char* name,
                    unsigned int thresholdDistanceMM,
                    float orientationRadian,
                    int* object);

// UTILS FUNCTION

/**
 * Returns if the tof distance under the Threshold (which means that we detects
 * something)
 * @param tofSensor
 * @return true if distance > 0 & <= threshold of TofSensor
 */
bool isTofDistanceUnderThreshold(TofSensor* tofSensor);

/**
 * We compute the real point of the tofSensor by taking into account
 * - The point of view (robotCentralPoint) and his orientation
 * - The position (polar coordinates) of the tofSensor
 * - The distance to the center of the Robot
 */
void tofComputeTofPointOfView(TofSensor* tofSensor, Point* robotCentralPoint, float robotOrientation, Point* resultPoint);

void tofComputePoint(TofSensor* tofSensor,
    Point* tofPointOfView,
    float pointOfViewAngleRadian,
    float distance,
    float coneAngle,
    Point* resultPoint);

/**
 * Compute if a something is detected from the pointOfView (Robot->position and robot->angle) and if something is detected,
 * them the point given in parameter will be updated.
 * @return true if a something was detected
 */
bool tofComputeDetectedPointIfAny(TofSensor* tofSensor, Point* pointOfView, float pointOfViewAngleRadian, Point* pointToUpdateIfAny);

/**
 * Is the tof sensor backward oriented, and in this case, we don't check them
 * when we go forward 
 */
bool isTofSensorBackwardOriented(TofSensor* tofSensor);

#endif