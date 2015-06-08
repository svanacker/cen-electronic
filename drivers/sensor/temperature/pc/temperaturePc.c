#include "temperaturePc.h"

#include <stdlib.h>

#include "../../../../common/sensor/temperature/temperature.h"

int _temperaturePc_readSensorValue(Temperature* temperature) {
    // Random Value : just to simulate
    return 25;
}

void _temperaturePc_writeAlertLimit(Temperature* temperature, int temperatureSensorAlertValue) {
    // DO Nothing
}

void initTemperaturePc(Temperature* temperature) {
    initTemperature(temperature, _temperaturePc_readSensorValue, _temperaturePc_writeAlertLimit, NULL);
}