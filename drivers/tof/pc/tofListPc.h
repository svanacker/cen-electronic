#ifndef TOF_LIST_PC_H
#define TOF_LIST_PC_H

#include <stdbool.h>

#include "../tofList.h"

void initTofSensorListPc(TofSensorList* tofSensorList, TofSensor(*tofSensorArray)[], unsigned int size);

#endif