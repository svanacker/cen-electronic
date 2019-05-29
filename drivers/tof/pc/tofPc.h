#ifndef TOF_PC_H
#define TOF_PC_H

#include <stdbool.h>

#include "../tof.h"

#define TOF_PC_BEAM_ANGLE_DEGREE             25.0f

void initTofSensorPc(TofSensor* tofSensor, int* object);

#endif