#ifndef MAIN_PHARE_2020_TOF_H
#define MAIN_PHARE_2020_TOF_H

// How many multiplexer are present in the lighthouse
#define MAIN_PHARE_2020_MULTIPLEXER_LIST_LENGTH                           1

// How many expander are present in the lighthouse                             
#define MAIN_PHARE_2020_IO_EXPANDER_LIST_LENGTH                           1

// Only 2 tof (left and right) even if we could handle up to 6 sensors on 
// Main Board
#define MAIN_PHARE_2020_TOF_SENSOR_LIST_COUNT                             2

#include "../../common/i2c/i2cBusList.h"

#include "../../drivers/i2c/multiplexer/multiplexerList.h"

#include "../../drivers/tof/tofList.h"

void mainLightHouse2020TofAddDevices(void);

TofSensorList* mainLightHouse2020TofInitDrivers(I2cBus* i2cBus);

#endif
