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

void initTofSensorPc(TofSensor* tofSensor) {
    tofSensor->type = TOF_SENSOR_TYPE_PC;
    initTofSensor(tofSensor, 
                 &tofSensorInitPc, 
                 &tofSensorGetDistanceMMPc,
                 NULL);
}
