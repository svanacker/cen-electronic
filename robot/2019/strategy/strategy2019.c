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

#include "../../../robot/2019/bigRobot/bigRobotPath2019.h"
#include "../../../robot/2019/bigRobot/bigRobotStrategy2019.h"
#include "../../../robot/2019/bigRobot/bigRobotLocation2019.h"

#include "../../../robot/2019/fork/fork2019.h"
#include "../../../robot/2019/fork/forkDevice2019.h"

#include "../../../robot/2019/navigation/angle2019.h"
#include "../../../robot/2019/navigation/location2019.h"
#include "../../../robot/2019/navigation/path2019.h"

#include "../../../robot/2019/smallRobot/smallRobotLocation2019.h"
#include "../../../robot/2019/smallRobot/smallRobotPath2019.h"
#include "../../../robot/2019/smallRobot/smallRobotStrategy2019.h"

#include "../../../robot/2019/strategy/teamColor2019.h"

#include "../../../robot/2019/strategy/strategy2019.h"
#include "../../../robot/2019/strategy/strategy2019Utils.h"
#include "../../../robot/2019/strategy/strategyConfig2019.h"

void initColorAndStartPosition2019(GameStrategyContext* gameStrategyContext) {
    RobotConfig* robotConfig = gameStrategyContext->robotConfig;
    unsigned int configValue = robotConfig->robotConfigReadInt(robotConfig);

    // Configure the color so that we could use isViolet after, could NOT be used before !
    if (configValue & CONFIG_COLOR_YELLOW_MASK) {
        gameStrategyContext->color = TEAM_COLOR_2019_YELLOW;
    }
    else {
        gameStrategyContext->color = TEAM_COLOR_2019_VIOLET;
    }
    float angleDeciDegree = 0;
    enum RobotType robotType = robotConfig->robotType;
    if (robotType == ROBOT_TYPE_BIG) {
        gameStrategyContext->robotPosition->x = BIG_ROBOT_START_AREA_X;
        gameStrategyContext->robotPosition->y = BIG_ROBOT_START_AREA_Y;
        angleDeciDegree = BIG_ROBOT_START_AREA_ANGLE_DECI_DEG;
    }
    else if (robotType == ROBOT_TYPE_SMALL) {
        gameStrategyContext->robotPosition->x = SMALL_ROBOT_START_AREA_X;
        gameStrategyContext->robotPosition->y = SMALL_ROBOT_START_AREA_Y;
        angleDeciDegree = SMALL_ROBOT_START_AREA_ANGLE_DECI_DEG;
    }
    // Symetry
	if (isViolet(gameStrategyContext)) {
        angleDeciDegree = -angleDeciDegree;
        gameStrategyContext->robotPosition->y = GAMEBOARD_HEIGHT - gameStrategyContext->robotPosition->y;
	}
    float angleRadian = mod2PI(deciDegreeToRad(angleDeciDegree));
    gameStrategyContext->robotAngleRadian = angleRadian;
}

Location* addLocationWithColors(enum TeamColor teamColor, Navigation* navigation, char* name, char* label, float x, float y) {
    LocationList* locationList = navigation->locationList;
    if (teamColor == TEAM_COLOR_2019_VIOLET) {
        y = GAMEBOARD_HEIGHT - y;
    }
    Location* result = addNamedLocation(locationList, name, label, x, y);
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

    if (teamColor == TEAM_COLOR_2019_VIOLET) {
        angle1 = mod2PI(-angle1);
        angle2 = mod2PI(-angle2);
    }

    initPathData(pathData, location1, location2, cost, controlPointDistance1, controlPointDistance2, angle1, angle2, accelerationFactor, speedFactor);
    return pathData;
}

void initStrategy2019(GameStrategyContext* gameStrategyContext) {
    initColorAndStartPosition2019(gameStrategyContext);
    showGameStrategyContextTeamColorAndStrategy(gameStrategyContext);

    gameStrategyContext->defaultAccelerationFactor = getAccelerationFactor(gameStrategyContext->robotConfig);
    gameStrategyContext->defaultSpeedFactor = getSpeedFactor(gameStrategyContext->robotConfig);

    RobotConfig* robotConfig = gameStrategyContext->robotConfig;
    enum RobotType robotType = robotConfig->robotType;

    // We only load the item relative to the strategy Index chosen
    unsigned int strategyId = gameStrategyContext->strategyId;

    if (robotType == ROBOT_TYPE_SMALL) {
        initSmallRobotLocations2019(gameStrategyContext);
        initSmallRobotPaths2019(gameStrategyContext);

        initSmallRobotTargets2019(gameStrategyContext);
        initSmallRobotTargetActions2019(gameStrategyContext);
        initSmallRobotTargetActionsItems2019(gameStrategyContext);

        initSmallRobotStrategies2019(gameStrategyContext);
        if (strategyId != NO_STRATEGY_INDEX) {
            gameStrategyContext->gameStrategy = initSmallRobotStrategiesItems2019(gameStrategyContext);
        }
    }
    else if (robotType == ROBOT_TYPE_BIG) {
        initBigRobotLocations2019(gameStrategyContext);
        initBigRobotPaths2019(gameStrategyContext);

        initBigRobotTargets2019(gameStrategyContext);
        initBigRobotTargetActions2019(gameStrategyContext);
        initBigRobotTargetActionsItems2019(gameStrategyContext);

        initBigRobotStrategies2019(gameStrategyContext);

        if (strategyId != NO_STRATEGY_INDEX) {
            gameStrategyContext->gameStrategy = initBigRobotStrategiesItems2019(gameStrategyContext);
        }
    }
    else {
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
