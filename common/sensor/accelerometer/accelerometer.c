#include "accelerometer.h"

void initAccelerometer(Accelerometer* accelerometer, 
                       AccelerometerData* accelerometerData,
                       AccelerometerGetSampleCountFunction* getSampleCount,
                       AccelerometerReadLastSampleFunction* readLastSample,
                       // THRESHOLD
                       AccelerometerGetThresholdMilliGFunction* getThresholdMillig,
                       AccelerometerSetThresholdMilliGFunction* setThresholdMillig,
                       // DEBUG
                       AccelerometerDebugConfigFunction* debugConfig,
                       AccelerometerDebugConfigFunction* debugValues,
                       int* object) {
    accelerometer->accelerometerData = accelerometerData;
    accelerometer->getSampleCount = getSampleCount;
    accelerometer->readLastSample = readLastSample;
    accelerometer->getThresholdMillig = getThresholdMillig;
    accelerometer->setThresholdMillig = setThresholdMillig;
    accelerometer->debugConfig = debugConfig;
    accelerometer->debugValues = debugValues;
    accelerometer->object = object;
}