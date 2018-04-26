#include "colorSensorTcs34725.h"

#include <stdbool.h>
#include <stdlib.h>
#include "../../../common/color/color.h"
#include "../../../common/i2c/i2cBusConnectionList.h"

#include "tcs34725.h"

/**
 * @private
 * To get underlying object on PC
 */
Color* colorSensorTcs34725GetColor(ColorSensor* colorSensor) {
    return (Color*)colorSensor->object;
}

/**
 * 
 * @param colorSensor
 * @return 
 */
Tcs34725* colorSensorTcs34725GetTcs34725(ColorSensor* colorSensor) {
    return (Tcs34725*) colorSensor->object;
}

/**
 * ColorSensor Implementation (POO)
 */
bool colorSensorTcs34725Init(ColorSensor* colorSensor) {
    Tcs34725* tcs34725 = colorSensorTcs34725GetTcs34725(colorSensor);
    return tcs34725_begin(tcs34725);
}

/**
* ColorSensor Implementation (POO)
*/
Color* colorSensorTcs34725ReadValue(ColorSensor* colorSensor) {
    Tcs34725* tcs34725 = colorSensorTcs34725GetTcs34725(colorSensor);
    Color* color = colorSensor->color; 
    uint16_t r;
    uint16_t g;
    uint16_t b;
    uint16_t c;
    tcs34725_getRawData(tcs34725, &r, &g, &b, &c);
    color->R = r;
    color->G = g;
    color->B = b;
    return color;
}

void initColorSensorTcs34725(ColorSensor* colorSensor,
                             Color* color,
                             colorSensorFindColorTypeFunction* colorSensorFindColorType,
                             Tcs34725* tcs34725) {
    initColorSensor(colorSensor, 
                    &colorSensorTcs34725Init,
                    &colorSensorTcs34725ReadValue,       
                    colorSensorFindColorType,
                    color,
                    (int*) tcs34725);
}
