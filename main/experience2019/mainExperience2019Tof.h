#ifndef MAIN_EXPERIENCE_2019_TOF_H
#define MAIN_EXPERIENCE_2019_TOF_H

// How many multiplexer are present in the experience
#define MAIN_EXPERIENCE_2019_MULTIPLEXER_LIST_LENGTH                           1

// How many expander are present in the experience                             
#define MAIN_EXPERIENCE_2019_IO_EXPANDER_LIST_LENGTH                           1

// Only 2 tof (left and right) even if we could handle up to 6 sensors on 
// Main Board
#define MAIN_EXPERIENCE_2019_TOF_SENSOR_LIST_COUNT                             2

#include "../../common/i2c/i2cBusList.h"

#include "../../drivers/i2c/multiplexer/multiplexerList.h"

#include "../../drivers/tof/tofList.h"

void mainExperience2019TofAddDevices(void);

TofSensorList* mainExperience2019TofInitDrivers(I2cBus* i2cBus);

#endif
