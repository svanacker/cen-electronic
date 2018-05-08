#include "strategyAction2018.h"
#include "launcherDeviceInterface2018.h"
#include "strategy2018.h"

#include "../../client/motion/extended/clientExtendedMotion.h"
#include "../../client/robot/2018/launcherClient2018.h"

#include "../../common/error/error.h"

#include "../../motion/extended/bsplineMotion.h"

#include "../../robot/gameboard/gameboard.h"
#include "../../robot/strategy/teamColor.h"
#include "../../robot/strategy/gameStrategyContext.h"

#include <stdbool.h>

/**
* @private
*/
enum TeamColor getStrategy2018TeamColor(int* context) {
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)context;
    enum TeamColor teamColor = gameStrategyContext->color;

    return teamColor;
}

bool switch2018On(int* context) {
    enum TeamColor teamColor = getStrategy2018TeamColor(context);
    if (teamColor == TEAM_COLOR_GREEN) {
        return clientLightOn2018(LAUNCHER_RIGHT_INDEX);
    }
    else if (teamColor == TEAM_COLOR_ORANGE) {
        return clientLightOn2018(LAUNCHER_LEFT_INDEX);
    }
    writeError(WRONG_COLOR);
    return false;
}

// DISTRIBUTORS 

bool distributor1_2018(int* context) {
    enum TeamColor teamColor = getStrategy2018TeamColor(context);
    if (teamColor == TEAM_COLOR_GREEN) {
        return false;
    }
    else if (teamColor == TEAM_COLOR_ORANGE) {
        return false;
    }
    writeError(WRONG_COLOR);
    return false;
}

bool distributor2_2018(int* context) {
    return false;
}

bool garbageRelease_2018(int* context) {
    return false;
}

// BEE

bool bee2018(int* context) {
    enum TeamColor teamColor = getStrategy2018TeamColor(context);
    if (teamColor == TEAM_COLOR_GREEN) {
        return clientExtendedMotionBSplineAbsolute(BEE_X, BEE_Y, BEE_ANGLE_DECI_DEG, 1.0f, 1.0f, MOTION_ACCELERATION_FACTOR_HIGH, MOTION_SPEED_FACTOR_HIGH);
    }
    else if (teamColor == TEAM_COLOR_ORANGE) {
        return clientExtendedMotionBSplineAbsolute(BEE_X, GAMEBOARD_HEIGHT - BEE_Y, BEE_ANGLE_DECI_DEG, 1.0f, 1.0f, MOTION_ACCELERATION_FACTOR_HIGH, MOTION_SPEED_FACTOR_HIGH);
    }
    writeError(WRONG_COLOR);
    return false;
}