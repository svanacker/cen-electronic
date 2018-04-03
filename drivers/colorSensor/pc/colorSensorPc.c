#include "colorSensorPc.h"

#include <stdbool.h>
#include <stdlib.h>
#include "../../../common/color/color.h"

/**
 * @private
 * To get underlying object on PC
 */
Color* colorSensorPcGetColor(ColorSensor* colorSensor) {
    return (Color*)colorSensor->object;
}

/**
 * ColorSensor Implementation (POO)
 */
bool colorSensorPcInit(ColorSensor* colorSensor) {
    return true;
}

/**
* ColorSensor Implementation (POO)
*/
Color* colorSensorPcReadValue(ColorSensor* colorSensor) {
    return colorSensorPcGetColor(colorSensor);
}

void initColorSensorPc(ColorSensor* colorSensor, Color* pColor) {
    initColorSensor(colorSensor, &colorSensorPcInit, &colorSensorPcReadValue, (int*) pColor);
}
