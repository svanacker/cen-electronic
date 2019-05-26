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

void internalTofSensorListBeep(TofSensorList* tofSensorList, bool beepValue, bool overrideLock) {
    if (tofSensorList->beepLocked && !overrideLock) {
        return;
    }
    IOExpander* beepIoExpander = tofSensorList->beepIoExpander;
    if (beepIoExpander == NULL) {
        writeError(IO_EXPANDER_NULL);
        return;
    }
    if (tofSensorList->beepValue != beepValue) {
        tofSensorList->beepValue = beepValue;
        beepIoExpander->ioExpanderWriteSingleValue(beepIoExpander, tofSensorList->groundBeepIoPin, false);
        beepIoExpander->ioExpanderWriteSingleValue(beepIoExpander, tofSensorList->vccBeepIoPin, beepValue);
    }
}

void tofSensorListBeep(TofSensorList* tofSensorList, bool beepValue) {
    internalTofSensorListBeep(tofSensorList, beepValue, false);
}

void tofSensorListBeepOverrideLock(TofSensorList* tofSensorList, bool beepValue) {
    internalTofSensorListBeep(tofSensorList, beepValue, true);
}

unsigned int getTofSensorListSize(TofSensorList* tofSensorList) {
    return tofSensorList->size;
}

void tofSensorListResetDetectionCount(TofSensorList* tofSensorList) {
    if (tofSensorList == NULL) {
        writeError(TOF_SENSOR_LIST_NULL);
        return;
    }
    unsigned int i;
    unsigned int tofSensorListSize = tofSensorList->size;
    for (i = 0; i < tofSensorListSize; i++) {
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, i);
        tofSensor->detectedCount = 0;
    }
}

// UTILS METHODS

void tofSensorListSetEnableUsageType(TofSensorList* tofSensorList, enum TofSensorUsageType usageType, bool enabled) {
    if (tofSensorList == NULL) {
        writeError(TOF_SENSOR_LIST_NULL);
        return;
    }

    unsigned int i;
    unsigned int tofSensorListSize = tofSensorList->size;
    for (i = 0; i < tofSensorListSize; i++) {
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, i);
        if (tofSensor->usageType == usageType) {
            tofSensor->enabled = enabled;
        }
    }
    
}
