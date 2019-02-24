#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include "../../../common/io/outputStream.h"

// forward declaration
struct Accelerometer;
typedef struct Accelerometer Accelerometer;

/**
 * Universal accelerometer Value container.
 */
typedef struct AccelerometerData {
    // To know if we are in 2G, 4G, 8G or 16G sensibility
    unsigned char rangeMask;
    unsigned char xRawLowValue;
    unsigned char yRawLowValue;
    unsigned char zRawLowValue;
    unsigned char xRawHighValue;
    unsigned char yRawHighValue;
    unsigned char zRawHighValue;   
    
    int xRawValue;
    int yRawValue;
    int zRawValue;
    // Value in milliG
    float milligXValue;
    float milligYValue;
    float milligZValue;
} AccelerometerData;

/**
 * Function used to read the amount of Sample available.
 * @param accelerometer the instance object
 */
typedef unsigned int AccelerometerGetSampleCountFunction(Accelerometer* accelerometer);

/**
 * Function used to read the last Sample.
 * @param accelerometer the instance object
 */
typedef void AccelerometerReadLastSampleFunction(Accelerometer* accelerometer);

// THRESHOLD

typedef unsigned int AccelerometerGetThresholdMilliGFunction(Accelerometer* accelerometer);

typedef void AccelerometerSetThresholdMilliGFunction(Accelerometer* accelerometer, unsigned int tresholdMilliG);

// DEBUG

/**
 * Function used to debug the registers.
 * @param accelerometer the instance object
 */
typedef void AccelerometerDebugConfigFunction(OutputStream* outputStream, Accelerometer* accelerometer);

/**
 * Function used to debug the values.
 * @param accelerometer the instance object
 */
typedef void AccelerometerDebugValuesFunction(OutputStream* outputStream, Accelerometer* accelerometer);

/**
 * Define the contract for an accelerometer.
 */
struct Accelerometer {
    /** Stored data for the accelerometer */
    AccelerometerData* accelerometerData;
    /** The function which must be used to read the amount of sample available. */
    AccelerometerGetSampleCountFunction* getSampleCount;
    // DATA
    /** The function to read the last sample */
    AccelerometerReadLastSampleFunction* readLastSample;
    // TRESHOLD
    AccelerometerGetThresholdMilliGFunction* getThresholdMillig;
    AccelerometerSetThresholdMilliGFunction* setThresholdMillig;
    // DEBUG
    /** The function used to debug the config/registers */
    AccelerometerDebugConfigFunction* debugConfig;
    /** The function used to debug the values */
    AccelerometerDebugConfigFunction* debugValues;
    /** A pointer on generic object (for example to store I2cBus ...). */
    void* object;
};

/**
 * Init an accelerometer with his callback functions.
 * @param accelerometer
 * @param accelerometerData
 * @param getSampleCount the function which gives the amount of data available
 * @param readLastSample the function which read the last sampleData
 * @param debugConfig debug the general configuration of the accelerometer
 * @param debugValues to see the values of accelerometer but in a readable format
 */
void initAccelerometer(Accelerometer* accelerometer, 
                       AccelerometerData* accelerometerData,
                       AccelerometerGetSampleCountFunction* getSampleCount,
                       AccelerometerReadLastSampleFunction* readLastSample,
                       // THRESHOLD
                       AccelerometerGetThresholdMilliGFunction* getThresholdMillig,
                       AccelerometerSetThresholdMilliGFunction* setThresholdMillig,
                       // DEBUG
                       AccelerometerDebugConfigFunction* debugConfig,
                       AccelerometerDebugValuesFunction* debugValues,
                       int* object
        );

#endif
