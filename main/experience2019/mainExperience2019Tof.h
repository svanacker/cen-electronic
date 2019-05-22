#ifndef MAIN_EXPERIENCE_2019_TOF_H
#define MAIN_EXPERIENCE_2019_TOF_H

// Only 2 tof (left and right) even if we could handle up to 6 sensors on 
// Main Board
#define MAIN_EXPERIENCE_2019_TOF_SENSOR_LIST_COUNT                             2

#include "../../drivers/tof/tofList.h"

void mainExperience2019TofAddDevices(void);

TofSensorList* mainExperience2019TofInitDrivers(void);

#endif
