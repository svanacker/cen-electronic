#include "currentPc.h"

#include <stdlib.h>

#include "../../../../common/sensor/current/current.h"

int _currentPc_readSensorValue(Current* current) {
    // Random Value : just to simulate
    return 12;
}

void _currentPc_writeAlertLimit(Current* current, int currentSensorAlertValue) {
    // DO Nothing
}

void initCurrentPc(Current* current) {
    initCurrent(current, _currentPc_readSensorValue, _currentPc_writeAlertLimit, NULL);
}