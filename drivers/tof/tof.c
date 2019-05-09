#include "tof.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../../common/2d/2d.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"

#include "../../common/math/cenMath.h"

void initTofSensor(TofSensor* tofSensor, 
                    tofSensorInitFunction* tofSensorInit,
                    tofSensorGetDistanceMMFunction* tofGetDistanceMM,
                    char* name,
                    unsigned int thresholdDistanceMM,
                    float orientationRadian,
                    int* object) {
    tofSensor->tofSensorInit = tofSensorInit;
    tofSensor->tofGetDistanceMM = tofGetDistanceMM;
    tofSensor->name = name;
    tofSensor->lastDistanceMM = 0;
    tofSensor->thresholdDistanceMM = thresholdDistanceMM;
    tofSensor->orientationRadian = orientationRadian;
    tofSensor->object = object;
    tofSensor->tofSensorInit(tofSensor);
}

bool isTofDistanceUnderThreshold(TofSensor* tofSensor) {
    unsigned int distance = tofSensor->lastDistanceMM;

    // distance != 0 (means tof problem while measuring)
    // distance <= threshold
    return (distance != 0 && distance < tofSensor->thresholdDistanceMM);
}

bool tofComputeDetectedPointIfAny(TofSensor* tofSensor, Point* pointOfView, float pointOfViewAngleRadian, Point* pointToUpdateIfAny) {
    unsigned int distance = tofSensor->lastDistanceMM;
    // If No Point of View is provided
    if (pointOfView == NULL) {
        return false;
    }
    if (!isTofDistanceUnderThreshold(tofSensor)) {
        // we do not provide any point
        return false;      
    }
    // we compute the projection of the point along the point of view angle
    computeDirectionPoint(pointOfView, pointToUpdateIfAny, (float) distance, pointOfViewAngleRadian + tofSensor->orientationRadian);
    
    return true;
}

bool isTofSensorBackwardOriented(TofSensor* tofSensor) {
    return (tofSensor->orientationRadian > (PI / 2.0f) || 
            tofSensor->orientationRadian < (-PI / 2.0f));
}