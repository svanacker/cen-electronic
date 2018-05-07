#include "tofPc.h"

#include "../tof.h"

#include <stdbool.h>
#include <stdlib.h>

/**
 * Tof POO Implementation for PC
 * @private
*/
bool tofSensorInitPc(TofSensor* TofSensor) {
    return true;
}

/**
* Tof POO Implementation for PC
* @private
*/
unsigned int tofSensorGetDistanceMMPc(TofSensor* TofSensor) {
    return 100;
}

void initTofSensorPc(TofSensor* tofSensor, 
                    unsigned int thresholdDistanceMM,
                    float orientationRadian) {
    initTofSensor(tofSensor, 
                 &tofSensorInitPc, 
                 &tofSensorGetDistanceMMPc,
                 thresholdDistanceMM,
                 orientationRadian,
                 NULL);
}
