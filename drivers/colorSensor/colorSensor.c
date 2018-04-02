#include "colorSensor.h"

void initColorSensor(ColorSensor* colorSensor,
    colorSensorInitFunction* colorSensorInit,
    colorSensorReadValueFunction* colorSensorReadValue,
    int* object) {
    colorSensor->colorSensorInit = colorSensorInit;
    colorSensor->colorSensorReadValue = colorSensorReadValue;
    colorSensor->object = object;
}