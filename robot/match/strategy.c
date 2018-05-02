#include "strategy.h"
#include "teamColor.h"

#include "../../client/motion/position/clientTrajectory.h"

#include "../../robot/config/robotConfig.h"
#include "../../robot/config/robotConfigDevice.h"


/**
* The side for the match.
*/
static enum TeamColor teamColor;

void loadMatchSideAndUpdateRobotPosition(RobotConfig* robotConfig) {
    if (isConfigSet(robotConfig, CONFIG_COLOR_GREEN_MASK)) {
        teamColor = TEAM_COLOR_GREEN;
    }
    else {
        teamColor = TEAM_COLOR_ORANGE;
    }
    // TODO : Write on LCD
    // writeStringCR(getMatchSideAsString());
}

enum TeamColor getTeamColor() {
    return teamColor;
}


