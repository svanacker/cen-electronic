#include "colorSensor.h"

void initColorSensor(ColorSensor* colorSensor,
        colorSensorInitFunction* colorSensorInit,
        colorSensorReadValueFunction* colorSensorReadValue,
        colorSensorFindColorTypeFunction* colorSensorFindColorType,
        Color* color,
        int* object) {
    colorSensor->colorSensorInit = colorSensorInit;
    colorSensor->colorSensorReadValue = colorSensorReadValue;
    colorSensor->colorSensorFindColorType = colorSensorFindColorType;
    colorSensor->color = color;
    colorSensor->object = object;
}