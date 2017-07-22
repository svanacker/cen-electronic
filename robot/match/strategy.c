#include "strategy.h"
#include "teamColor.h"

#include "../../robot/config/robotConfig.h"
#include "../../robot/config/robotConfigDevice.h"

#include "../../drivers/motion/trajectoryDriver.h"

/**
* The side for the match.
*/
static enum TeamColor teamColor;

void loadMatchSideAndUpdateRobotPosition(RobotConfig* robotConfig) {
    if (isConfigSet(robotConfig, CONFIG_COLOR_GREEN_MASK)) {
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


