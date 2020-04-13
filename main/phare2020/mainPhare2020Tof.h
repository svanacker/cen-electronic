#ifndef MAIN_PHARE_2020_TOF_H
#define MAIN_PHARE_2020_TOF_H

// How many multiplexer are present in the lighthouse
#define MAIN_PHARE_2020_MULTIPLEXER_LIST_LENGTH                           1

// How many expander are present in the lighthouse                             
#define MAIN_PHARE_2020_IO_EXPANDER_LIST_LENGTH                           1

// Only 1 tof on Main Board for TOF
#define MAIN_PHARE_2020_TOF_SENSOR_LIST_COUNT                             1

// The I2C Bus Index for I2C_PORT_1
#define MAIN_PHARE_2020_MAIN_I2C_BUS_INDEX                                0

#include "../../common/i2c/i2cBusList.h"

#include "../../drivers/i2c/multiplexer/multiplexerList.h"

#include "../../drivers/tof/tofList.h"

void mainLightHouse2020TofAddDevices(void);

TofSensorList* mainLightHouse2020TofInitDrivers(I2cBus* i2cBus);

#endif
