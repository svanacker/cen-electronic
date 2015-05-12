#include "strategy.h"
#include "teamColor.h"

#include "../../robot/config/robotConfig.h"
#include "../../robot/config/robotConfigDevice.h"

#include "../../drivers/motion/trajectoryDriver.h"
// #include "../../device/drivers/lcd.h"

/**
* The side for the match.
*/
static enum TeamColor teamColor;

void loadMatchSideAndUpdateRobotPosition(void) {
    teamColor = getConfigValue() & CONFIG_COLOR_GREEN_MASK;
    if (teamColor != 0) {
        teamColor = COLOR_GREEN;
    }
    else {
        teamColor = COLOR_YELLOW;
    }
    // TODO : Write on LCD
    // writeStringCR(getMatchSideAsString());
}

enum TeamColor getTeamColor() {
    return teamColor;
}


