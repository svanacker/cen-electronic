#ifndef TOF_PC_H
#define TOF_PC_H

#include <stdbool.h>

#include "../tof.h"

void initTofSensorPc(TofSensor* tofSensor,
                     char* name,
                     unsigned int thresholdDistanceMM,
                     float orientationRadian);

#endif