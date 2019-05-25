#ifndef TOF_H
#define TOF_H

#include <stdbool.h>

#include "../../drivers/i2c/multiplexer/multiplexer.h"

// Forward declaration
typedef struct TofSensor TofSensor;

/**
 * Real implementation of start, or restart
 */
typedef bool tofSensorStartFunction(TofSensor* TofSensor, bool restart, bool debug);

/**
 * Define the function which must be used to get the distance 
 */
typedef unsigned int tofSensorGetDistanceMMFunction(TofSensor* tofSensor);

/**
 * Type of TofSensor (VL530X or PC for the moment)
 */
enum TofSensorType {
    /** The user type was not defined */
    TOF_SENSOR_TYPE_UNKNOWN = 0,
    /** The Hardware version type. */
    TOF_SENSOR_TYPE_VL53L0X = 1,
    /** The Simulated type on PC. */
    TOF_SENSOR_TYPE_PC = 2,
};

/**
 * Type of TofSensor, some are used to detect collision, are used for actions
 */
enum TofSensorUsageType {
    /** The user type was not defined */
    TOF_SENSOR_USAGE_TYPE_UNKNOWN = 0,
    /** The tof is used to detect Collision. */
    TOF_SENSOR_USAGE_TYPE_COLLISION = 1,
    /** The tof is used to detect actions. */
    TOF_SENSOR_USAGE_TYPE_ACTION = 2
};

/**
 * Enum to determine how was the latest start, if the tof was successful 
 * started or not
 */
enum TofSensorStartResult {
    TOF_SENSOR_START_RESULT_UNKNOWN = 0,
    TOF_SENSOR_START_RESULT_DISABLED = 1,
    TOF_SENSOR_START_RESULT_OK = 2,
    TOF_SENSOR_START_RESULT_ALREADY_STARTED = 3,
    TOF_SENSOR_START_RESULT_INIT_PROBLEM = 4,
    TOF_SENSOR_START_RESULT_CHANGE_ADDRESS_PROBLEM = 5,
    
};

/**
* Defines the contract For one Tof Sensor.
*/
struct TofSensor {
    /** An name for the sensor. */
    char* name;
    /** The type of Sensor. */
    enum TofSensorType type;
    /** The usage type of Sensor. */
    enum TofSensorUsageType usageType;
    /** The latest status of start for this Sensor. */
    enum TofSensorStartResult startResult;
    /** If we enabled it. If disable, we do not try to initialize it .*/
    bool enabled;
    
    // NETWORK
    /** The i2cBus index which must be used .*/
    unsigned int i2cBusIndex;
    /** If we must change the address of the TOF at startup .*/
    bool changeAddress;
    /** The new address that we would like to reach */
    unsigned int targetAddress;
    /** The multiplexer (could be null if not used). */
    Multiplexer* multiplexer;
    /** The channel to use inside the multiplexer if we use it (MULTIPLEXER_CHANNEL_0 to MULTIPLEXER_CHANNEL_7). */
    unsigned int multiplexerChannel;
    
    // RESTART
    /** If the tof is connected to a mechanism which could restart it */
    bool hardwareRestartable;
    /** The index of the IOExpander. */
    unsigned int hardwareRestartIOExpanderIndex;
    /** The index of the IO, which is connected to the XShut pin of the tof  */
    unsigned int hardwareRestartIOExpanderIoIndex;
    
    // DISTANCE & TRESHOLD
    /** The function which must be used to read the distance */
    tofSensorGetDistanceMMFunction* tofGetDistanceMM;
    /** Stored the value of the last call */
    unsigned int lastDistanceMM;
    /** Stored the threshold min for which we would like that it raises a notification. */
    unsigned int thresholdMinDistanceMM;
    /** Stored the threshold min for which we would like that it raises a notification. */
    unsigned int thresholdMaxDistanceMM;
    /** The threshold of how many detections must be done before we consider that the measure is valid */
    unsigned int detectionThreshold;
    /** The counter of how many detected were done. */
    unsigned int detectedCount;
    
    // CONFIG
    /** The beam angle of what he could detect. */
    float beamAngleRadian;
    /** pointer on other object (useful for I2C Connection for example) .*/
    /** Store the angle in radian of the sensor compared to the robot. We use the same coordinates than for Robot. */
    float orientationRadian;
    /** The distance between the Sensor compared and the center of the robot. */
    float distanceFromRobotCenter;
    /** The angle of the central point of the Sensor compared to the center of the robot (with X axis along the going point). */
    float angleFromRobotCenterRadian;

    // IMPLEMENTATION CALL BACK
    /** The real function which do something on the Hardware */
    tofSensorStartFunction* tofSensorStart;
    
    // EXTENSION OBJECT
    /** Generic pointer for context use */
    int* object;
};

/**
 * Init a Tof Sensor
 */
void initTofSensor(TofSensor* tofSensor, 
                    tofSensorStartFunction* tofSensorStart,
                    tofSensorGetDistanceMMFunction* tofGetDistanceMM,
                    int* object);

/**
 * Start the Tof Sensor for the first time.
 * @param tofSensor
 * @return 
 */
bool tofStart(TofSensor* tofSensor);

/**
 * Restart a Tof Sensor (useful if the I2c Bus Connection has a problem).
 * @param tofSensor the tofSensor to restart
 * @return 
 */
bool tofRestart(TofSensor* tofSensor);

#endif