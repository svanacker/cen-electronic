#include "distributor2019.h"
#include "distributorDebug2019.h"

#include "../../common/color/color.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../robot/2019/score2019.h"
#include "../../robot/2019/teamColor2019.h"

#include "../../drivers/colorSensor/colorSensor.h"
#include "../../drivers/colorSensor/colorSensorDebug.h"

#include "../../robot/strategy/teamColor.h"


enum ColorType colorSensorFindColorType2019(ColorSensor* colorSensor) {
    Color* color = colorSensor->colorSensorReadValue(colorSensor);
    
    if (isColorInRange(color, 
        PUCK_2019_GREENIUM_R_LOW_THRESHOLD, 
        PUCK_2019_GREENIUM_R_HIGH_THRESHOLD,
        PUCK_2019_GREENIUM_G_LOW_THRESHOLD,
        PUCK_2019_GREENIUM_G_HIGH_THRESHOLD,
        PUCK_2019_GREENIUM_B_LOW_THRESHOLD,
        PUCK_2019_GREENIUM_B_HIGH_THRESHOLD)
        && (color->G > color->R)    
            ) {
        return COLOR_TYPE_GREEN;
        }
    else if (isColorInRange(color,
        PUCK_2019_BLUEIUM_R_LOW_THRESHOLD,
        PUCK_2019_BLUEIUM_R_HIGH_THRESHOLD,
        PUCK_2019_BLUEIUM_G_LOW_THRESHOLD,
        PUCK_2019_BLUEIUM_G_HIGH_THRESHOLD,
        PUCK_2019_BLUEIUM_B_LOW_THRESHOLD,
        PUCK_2019_BLUEIUM_B_HIGH_THRESHOLD)
        && (color->R > 2 * color->G)    
            ) {
        return COLOR_TYPE_BLUE;
    }
    else if (isColorInRange(color,
        PUCK_2019_REDIUM_R_LOW_THRESHOLD,
        PUCK_2019_REDIUM_R_HIGH_THRESHOLD,
        PUCK_2019_REDIUM_G_LOW_THRESHOLD,
        PUCK_2019_REDIUM_G_HIGH_THRESHOLD,
        PUCK_2019_REDIUM_B_LOW_THRESHOLD,
        PUCK_2019_REDIUM_B_HIGH_THRESHOLD)
        && (color->R > 2 * color->G)
        ) {
        return COLOR_TYPE_RED;
    }
    return COLOR_TYPE_UNKNOWN;
}

void initDistributor2019(BigDistributor* bigDistributor, enum TeamColor teamColor) {
    bigDistributor->teamColor = teamColor;
    // TODO : init
}
