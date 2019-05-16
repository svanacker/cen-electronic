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
                        bool debug,
                        bool enabledAllSensors,
                        bool changeAddressAllSensors,
                       tofSensorListDebugTableFunction* tofSensorListDebugTable) {
    if (tofSensorArray == NULL) {
        writeError(TOF_SENSOR_LIST_NOT_INITIALIZED);
    }
    tofSensorList->tofSensorArray = tofSensorArray;
    tofSensorList->size = tofSensorListSize;
    tofSensorList->debug = debug;
    tofSensorList->tofSensorListDebugTable = tofSensorListDebugTable;
    unsigned int i;
    for (i = 0; i < tofSensorListSize; i++) {
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, i);
        if (enabledAllSensors) {
            tofSensor->enabled = true;
        }
        if (changeAddressAllSensors) {
            tofSensor->changeAddress = true;
        }
    }
}

TofSensor* getTofSensorByIndex(TofSensorList* tofSensorList, unsigned int index) {
    if (tofSensorList == NULL || tofSensorList->tofSensorArray == NULL) {
        writeError(TOF_SENSOR_LIST_NOT_INITIALIZED);
        return NULL;
    }
	if (index < 0 || index >= tofSensorList->size) {
		writeError(TOF_SENSOR_LIST_ILLEGAL_INDEX);
        appendStringAndDecLN(getErrorOutputStreamLogger(), "Index = ", index);
		return NULL;
	}
	TofSensor* result = (TofSensor*)tofSensorList->tofSensorArray;
	// we don't need use sizeof because our pointer is a TofSensor pointer, so the shift
	// is already of the structure, we just have to shift of index.
	result += index;

	return result;
}

void tofSensorListBeep(TofSensorList* tofSensorList, bool value) {
    IOExpander* beepIoExpander = tofSensorList->beepIoExpander;
    if (beepIoExpander == NULL) {
        writeError(IO_EXPANDER_NULL);
        return;
    }
    if (tofSensorList->beepValue != value) {
        tofSensorList->beepValue = value;
        beepIoExpander->ioExpanderWriteSingleValue(beepIoExpander, 7, value);
    }
}

unsigned int getTofSensorListSize(TofSensorList* tofSensorList) {
    return tofSensorList->size;
}
