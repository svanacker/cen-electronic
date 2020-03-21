#include "tofListPc.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tofPc.h"
#include "tofListDebugPc.h"

#include "../../../common/math/cenMath.h"

#include "../tofList.h"
#include "../tofDebug.h"

#define TOF_NAME_PC_STRING_LENGTH   15

void initTofSensorListPc(TofSensorList* tofSensorList, TofSensor(*tofSensorArray)[], unsigned int size, int* object) {
    initTofSensorList(tofSensorList, tofSensorArray,
            size,
            true,
            &printTofSensorConfigTablePc,
            &printTofSensorNetworkTablePc,
            &printTofSensorDetectionTablePc
            );
    unsigned int tofIndex;
    for (tofIndex = 0; tofIndex < size; tofIndex++) {
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, tofIndex);
        initTofSensorPc(tofSensor, object);

        if (tofSensor->name == NULL) {
            char* tofName = (char*) malloc(TOF_NAME_PC_STRING_LENGTH * sizeof (char));
            snprintf(tofName, TOF_NAME_PC_STRING_LENGTH, "TOF PC ");
            snprintf(tofName + strlen(tofName), TOF_NAME_PC_STRING_LENGTH, "%d", tofIndex);
            tofSensor->name = tofName;
        }
        // When the whole initialization is done, we could start the tof !
        tofStart(tofSensor);
    }
}