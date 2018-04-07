#include "tofListPc.h"

#include <stdbool.h>
#include <stdlib.h>

#include "tofPc.h"

#include "../tofList.h"
#include "../tofDebug.h"

void initTofSensorListPc(TofSensorList* tofSensorList, TofSensor(*tofSensorArray)[], unsigned int size) {
    initTofSensorList(tofSensorList, tofSensorArray, size, &printTofSensorTable);
    unsigned int tofIndex;
    for (tofIndex = 0; tofIndex < size; tofIndex++) {
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, tofIndex);
        initTofSensorPc(tofSensor, 0);
    }
}