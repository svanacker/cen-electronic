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
    TofSensorListConfigTableDebugFunction* tofSensorListConfigTableDebug,
    TofSensorListNetworkTableDebugFunction* tofSensorListNetworkTableDebug,
    TofSensorListDetectionTableDebugFunction* tofSensorListDetectionTableDebug
) {
    if (tofSensorArray == NULL) {
        writeError(TOF_SENSOR_LIST_NOT_INITIALIZED);
    }
    tofSensorList->tofSensorArray = tofSensorArray;
    tofSensorList->size = tofSensorListSize;
    tofSensorList->debug = debug;
    tofSensorList->tofSensorListConfigTableDebug = tofSensorListConfigTableDebug;
    tofSensorList->tofSensorListNetworkTableDebug = tofSensorListNetworkTableDebug;
    tofSensorList->tofSensorListDetectionTableDebug = tofSensorListDetectionTableDebug;
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

void initTofSensorListBeep(TofSensorList* tofSensorList,
                           IOExpander* beepIoExpander,
                           unsigned int groundBeepIoPin,
                           unsigned int vccBeepIoPin) {
    tofSensorList->beepIoExpander = beepIoExpander;
    tofSensorList->groundBeepIoPin = groundBeepIoPin;
    tofSensorList->vccBeepIoPin = vccBeepIoPin;
}

void tofSensorListBeep(TofSensorList* tofSensorList, bool value) {
    IOExpander* beepIoExpander = tofSensorList->beepIoExpander;
    if (beepIoExpander == NULL) {
        writeError(IO_EXPANDER_NULL);
        return;
    }
    if (tofSensorList->beepValue != value) {
        tofSensorList->beepValue = value;
        beepIoExpander->ioExpanderWriteSingleValue(beepIoExpander, tofSensorList->groundBeepIoPin, false);
        beepIoExpander->ioExpanderWriteSingleValue(beepIoExpander, tofSensorList->vccBeepIoPin, value);
    }
}

unsigned int getTofSensorListSize(TofSensorList* tofSensorList) {
    return tofSensorList->size;
}

void tofSensorListResetDetectionCount(TofSensorList* tofSensorList) {
    unsigned int i;
    unsigned int tofSensorListSize = tofSensorList->size;
    for (i = 0; i < tofSensorListSize; i++) {
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, i);
        tofSensor->detectedCount = 0;
    }
}
