#include "colorSensorPc.h"

#include <stdbool.h>
#include <stdlib.h>
#include "../../../common/color/color.h"

bool colorSensorPcInit(ColorSensor* colorSensor) {
    return true;
}

Color* colorSensorPcReadValue(ColorSensor* colorSensor) {
    // TODO
    return NULL;
}

void initColorSensorPc(ColorSensor* colorSensor, Color* pColor) {
    initColorSensor(colorSensor, &colorSensorPcInit, &colorSensorPcReadValue, (int*) pColor);
}
