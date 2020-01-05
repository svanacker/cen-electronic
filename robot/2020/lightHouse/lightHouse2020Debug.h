#ifndef LIGHT_HOUSE_DEBUG_2020_H
#define LIGHT_HOUSE_DEBUG_2020_H

#include "lightHouse2020.h"

#include "../../../common/io/outputStream.h"


unsigned int printLightHouseState(OutputStream* outputStream, enum LightHouse2020State state);

unsigned int addLightHouseStateTypeTableData(OutputStream* outputStream, enum LightHouse2020State state, int columnSize);

/**
* Debug the launcher
*/
void lightHouse2020Debug(LightHouse2020* launcher, OutputStream* outputStream);


#endif
