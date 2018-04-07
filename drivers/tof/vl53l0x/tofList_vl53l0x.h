#ifndef TOF_LIST_VL53L0X_H
#define TOF_LIST_VL53L0X_H

#include <stdbool.h>

#include "../../../common/i2c/i2cBusList.h"

#include "tof_vl53l0x.h"

#include "../tof.h"
#include "../tofList.h"
#include "../../../drivers/ioExpander/ioExpander.h"

void initTofSensorListVL53L0X(TofSensorList* tofSensorList, 
                              TofSensor(*tofSensorArray)[],
                              TofSensorVL53L0X(*tofSensorVL53L0XArray)[],
                              unsigned int size,
                              I2cBus* i2cBus,
                              IOExpander* ioExpander);

#endif