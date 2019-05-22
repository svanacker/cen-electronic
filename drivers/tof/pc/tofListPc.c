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
                      NULL,
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
        initTofSensorPc(tofSensor);

        char* tofName = (char*)malloc(TOF_NAME_PC_STRING_LENGTH * sizeof(char));
        snprintf(tofName, TOF_NAME_PC_STRING_LENGTH, "TOF PC ");
        snprintf(tofName + strlen(tofName), TOF_NAME_PC_STRING_LENGTH, "%d", tofIndex);
        tofSensor->name = tofName;
    }
}