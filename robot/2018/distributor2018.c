#include "distributor2018.h"

#include "../../common/color/color.h"
#include "../../drivers/colorSensor/colorSensor.h"

enum ColorType colorSensorFindColorType2018(ColorSensor* colorSensor) {
    Color* color = colorSensor->colorSensorReadValue(colorSensor);
    
    if (isColorInRange(color, 
        DISTRIBUTOR_2018_GREEN_R_LOW_THRESHOLD, 
        DISTRIBUTOR_2018_GREEN_R_HIGH_THRESHOLD,
        DISTRIBUTOR_2018_GREEN_G_LOW_THRESHOLD,
        DISTRIBUTOR_2018_GREEN_G_HIGH_THRESHOLD,
        DISTRIBUTOR_2018_GREEN_B_LOW_THRESHOLD,
        DISTRIBUTOR_2018_GREEN_B_HIGH_THRESHOLD)) {
        return COLOR_TYPE_GREEN;
        }
    else if (isColorInRange(color,
        DISTRIBUTOR_2018_ORANGE_R_LOW_THRESHOLD,
        DISTRIBUTOR_2018_ORANGE_R_HIGH_THRESHOLD,
        DISTRIBUTOR_2018_ORANGE_G_LOW_THRESHOLD,
        DISTRIBUTOR_2018_ORANGE_G_HIGH_THRESHOLD,
        DISTRIBUTOR_2018_ORANGE_B_LOW_THRESHOLD,
        DISTRIBUTOR_2018_ORANGE_B_HIGH_THRESHOLD)) {
        return COLOR_TYPE_ORANGE;
    }
    return COLOR_TYPE_UNKNOWN;
}