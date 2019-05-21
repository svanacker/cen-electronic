#include "tofListPc.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tofPc.h"
#include "tofListDebugPc.h"

#include "../tofList.h"
#include "../tofDebug.h"

#define TOF_NAME_PC_STRING_LENGTH   15

void initTofSensorListPc(TofSensorList* tofSensorList, TofSensor(*tofSensorArray)[], unsigned int size) {
    initTofSensorList(tofSensorList, tofSensorArray,
                      size,
                      true,
                      true,
                      true,
                      &printTofSensorConfigTablePc,
                      &printTofSensorNetworkTablePc,
                      &printTofSensorDetectionTablePc
                      );
    unsigned int tofIndex;
    for (tofIndex = 0; tofIndex < size; tofIndex++) {
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, tofIndex);
        char* tofName = (char*)malloc(TOF_NAME_PC_STRING_LENGTH * sizeof(char));
        snprintf(tofName, TOF_NAME_PC_STRING_LENGTH, "TOF PC ");
        snprintf(tofName + strlen(tofName), TOF_NAME_PC_STRING_LENGTH, "%d", tofIndex);

        initTofSensorPc(tofSensor, tofName, 0, 0.0f);
    }
}