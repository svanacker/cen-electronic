#include "tofList.h"

#include <stdlib.h>
#include <stdbool.h>

#include "tof.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logHandler.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"


void initTofSensorList(TofSensorList* tofSensorList,
                       TofSensor(*tofSensorArray)[],
                       unsigned int tofSensorListSize,
                       tofSensorListDebugTableFunction* tofSensorListDebugTable) {
    if (tofSensorArray == NULL) {
        writeError(TOF_SENSOR_LIST_NOT_INITIALIZED);
    }
    tofSensorList->tofSensorArray = tofSensorArray;
    tofSensorList->size = tofSensorListSize;
    tofSensorList->tofSensorListDebugTable = tofSensorListDebugTable;
}

TofSensor* getTofSensorByIndex(TofSensorList* tofSensorList, unsigned int index) {
    if (tofSensorList == NULL || tofSensorList->tofSensorArray == NULL) {
        writeError(TOF_SENSOR_LIST_NOT_INITIALIZED);
        return NULL;
    }
	if (index < 0 || index >= tofSensorList->size) {
		writeError(TOF_SENSOR_LIST_ILLEGAL_INDEX);
		return NULL;
	}
	TofSensor* result = (TofSensor*)tofSensorList->tofSensorArray;
	// we don't need use sizeof because our pointer is a TofSensor pointer, so the shift
	// is already of the structure, we just have to shift of index.
	result += index;

	return result;
}

unsigned int getTofSensorListSize(TofSensorList* tofSensorList) {
    return tofSensorList->size;
}
