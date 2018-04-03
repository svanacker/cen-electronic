#include "colorSensor.h"

void initColorSensor(ColorSensor* colorSensor,
    colorSensorInitFunction* colorSensorInit,
    colorSensorReadValueFunction* colorSensorReadValue,
    Color* color,
    int* object) {
    colorSensor->colorSensorInit = colorSensorInit;
    colorSensor->colorSensorReadValue = colorSensorReadValue;
    colorSensor->color = color;
    colorSensor->object = object;
}