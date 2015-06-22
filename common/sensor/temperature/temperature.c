#include "temperature.h"

#include <stdlib.h>

#include "../../../common/error/error.h"

void initTemperature(Temperature* temperature,
    TemperatureReadSensorValueFunction* readSensorValue,
    TemperatureWriteAlertLimitFunction* writeAlertLimit,
    void* object) {
    if (temperature == NULL) {
        writeError(TEMPERATURE_NULL);
        return;
    }  
    temperature->readSensorValue = readSensorValue;
    temperature->writeAlertLimit = writeAlertLimit;
    temperature->object = object;
}
