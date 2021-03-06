#include <stdlib.h>

#include "../../../common/error/error.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/math/cenMath.h"

#include "../../../common/pwm/servo/servoList.h"

#include "../../../motion/motion.h"
#include "../../../motion/simple/simpleMotion.h"
#include "../../../motion/extended/bsplineMotion.h"

#include "../../../navigation/locationList.h"
#include "../../../navigation/path.h"
#include "../../../navigation/pathList.h"
#include "../../../navigation/pathListDebug.h"
#include "../../../navigation/navigation.h"

#include "../../../client/motion/position/clientTrajectory.h"

#include "../../../robot/config/robotConfig.h"

#include "../../../robot/gameboard/gameboard.h"

#include "../../../robot/strategy/gameStrategy.h"
#include "../../../robot/strategy/gameStrategyHandler.h"
#include "../../../robot/strategy/gameStrategyList.h"
#include "../../../robot/strategy/gameTargetList.h"
#include "../../../robot/strategy/gameTarget.h"
#include "../../../robot/strategy/gameTargetAction.h"
#include "../../../robot/strategy/gameTargetActionItem.h"
#include "../../../robot/strategy/gameTargetActionList.h"

#include "../../../robot/tof/strategyTofSensorList.h"

#include "../../../robot/2020/bigRobot/bigRobotPath2020.h"
#include "../../../robot/2020/bigRobot/bigRobotStrategy2020.h"
#include "../../../robot/2020/bigRobot/bigRobotLocation2020.h"

#include "../../../robot/2020/navigation/angle2020.h"
#include "../../../robot/2020/navigation/location2020.h"
#include "../../../robot/2020/navigation/path2020.h"

#include "../../../robot/2020/smallRobot/smallRobotLocation2020.h"
#include "../../../robot/2020/smallRobot/smallRobotPath2020.h"
#include "../../../robot/2020/smallRobot/smallRobotStrategy2020.h"

#include "../../../robot/2020/strategy/teamColor2020.h"

#include "../../../robot/2020/strategy/strategy2020.h"
#include "../../../robot/2020/strategy/strategy2020Utils.h"
#include "../../../robot/2020/strategy/strategyConfig2020.h"

void initColorAndStartPosition2020(GameStrategyContext* gameStrategyContext) {
    RobotConfig* robotConfig = gameStrategyContext->robotConfig;
    
    gameStrategyContext->color = getTeamColorFromRobotConfig(robotConfig);

    float angleDeciDegree = 0;
    enum RobotType robotType = getRobotType();
    if (robotType == ROBOT_TYPE_BIG) {
        gameStrategyContext->robotPosition->x = BIG_ROBOT_START_AREA_X;
        gameStrategyContext->robotPosition->y = BIG_ROBOT_START_AREA_Y;
        angleDeciDegree = BIG_ROBOT_START_AREA_ANGLE_DECI_DEG;
    } else if (robotType == ROBOT_TYPE_SMALL) {
        gameStrategyContext->robotPosition->x = SMALL_ROBOT_START_AREA_X;
        gameStrategyContext->robotPosition->y = SMALL_ROBOT_START_AREA_Y;
        angleDeciDegree = SMALL_ROBOT_START_AREA_ANGLE_DECI_DEG;
    }
    // Symetry
    if (isYellow2020(gameStrategyContext)) {
        angleDeciDegree = -angleDeciDegree;
        gameStrategyContext->robotPosition->y = GAMEBOARD_HEIGHT - gameStrategyContext->robotPosition->y;
    }
    float angleRadian = mod2PI(deciDegreeToRad(angleDeciDegree));
    gameStrategyContext->robotAngleRadian = angleRadian;
}

Location* addLocationWithColors(enum TeamColor teamColor, Navigation* navigation, char* name, char* label, float x, float y) {
    LocationList* locationList = navigation->locationList;
    if (teamColor == TEAM_COLOR_2020_YELLOW) {
        y = GAMEBOARD_HEIGHT - y;
    }
    Location* result = addNamedLocation(locationList, LOCATION_USAGE_TYPE_PERMANENT, name, label, x, y);
    return result;
}

// PATHS

PathData* addNavigationPathWithColor(
        enum TeamColor teamColor,
        Navigation* navigation,
        Location* location1,
        Location* location2,
        float cost,
        float controlPointDistance1,
        float controlPointDistance2,
        float angle1,
        float angle2,
        float accelerationFactor,
        float speedFactor) {
    PathData* pathData = addPath(navigation->paths);

    if (teamColor == TEAM_COLOR_2020_YELLOW) {
        angle1 = mod2PI(-angle1);
        angle2 = mod2PI(-angle2);
    }

    initPathData(pathData, PATH_DATA_USAGE_TYPE_PERMANENT, location1, location2, cost, controlPointDistance1, controlPointDistance2, angle1, angle2, accelerationFactor, speedFactor);
    return pathData;
}

void initStrategy2020(GameStrategyContext* gameStrategyContext) {
    initColorAndStartPosition2020(gameStrategyContext);
    showGameStrategyContextTeamColorAndStrategy(gameStrategyContext);

    gameStrategyContext->defaultAccelerationFactor = getAccelerationFactor(gameStrategyContext->robotConfig);
    gameStrategyContext->defaultSpeedFactor = getSpeedFactor(gameStrategyContext->robotConfig);

    enum RobotType robotType = getRobotType();

    // We only load the item relative to the strategy Index chosen
    unsigned int strategyId = gameStrategyContext->strategyId;

    if (robotType == ROBOT_TYPE_SMALL) {
        initSmallRobotLocations2020(gameStrategyContext);
        initSmallRobotPaths2020(gameStrategyContext);

        initSmallRobotTargets2020(gameStrategyContext);
        initSmallRobotTargetActions2020(gameStrategyContext);
        initSmallRobotTargetActionsItems2020(gameStrategyContext);

        initSmallRobotStrategies2020(gameStrategyContext);
        if (strategyId != NO_STRATEGY_INDEX) {
            gameStrategyContext->gameStrategy = initSmallRobotStrategiesItems2020(gameStrategyContext);
        }
    } else if (robotType == ROBOT_TYPE_BIG) {
        initBigRobotLocations2020(gameStrategyContext);
        initBigRobotPaths2020(gameStrategyContext);

        initBigRobotTargets2020(gameStrategyContext);
        initBigRobotTargetActions2020(gameStrategyContext);
        initBigRobotTargetActionsItems2020(gameStrategyContext);

        initBigRobotStrategies2020(gameStrategyContext);

        if (strategyId != NO_STRATEGY_INDEX) {
            gameStrategyContext->gameStrategy = initBigRobotStrategiesItems2020(gameStrategyContext);
        }
    } else {
        writeError(ROBOT_TYPE_UNKNOWN_ERROR);
    }

    // opponent
    Point* p = gameStrategyContext->opponentRobotPosition;
    p->x = 0;
    p->y = 0;

    // obstacle
    p = gameStrategyContext->lastObstaclePosition;
    p->x = 0;
    p->y = 0;

    // reinitialize the game board to change elements / targets ...
}
