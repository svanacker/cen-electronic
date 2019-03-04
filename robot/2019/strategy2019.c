#include <stdlib.h>

#include "strategy2019.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/math/cenMath.h"

#include "../../drivers/tof/tofList.h"

#include "../../motion/motion.h"
#include "../../motion/simple/simpleMotion.h"
#include "../../motion/extended/bsplineMotion.h"

#include "../../navigation/locationList.h"
#include "../../navigation/path.h"
#include "../../navigation/pathList.h"
#include "../../navigation/pathListDebug.h"
#include "../../navigation/navigation.h"

#include "../../client/motion/position/clientTrajectory.h"

#include "../../robot/config/robotConfig.h"

#include "../../robot/gameboard/gameBoard.h"

#include "../../robot/strategy/gameStrategy.h"
#include "../../robot/strategy/gameStrategyHandler.h"
#include "../../robot/strategy/gameStrategyList.h"
#include "../../robot/strategy/gameTargetList.h"
#include "../../robot/strategy/gameTarget.h"
#include "../../robot/strategy/gameTargetAction.h"
#include "../../robot/strategy/gameTargetActionItem.h"
#include "../../robot/strategy/gameTargetActionList.h"

#include "../../robot/tof/strategyTofSensorList.h"

#include "../../robot/2019/teamColor2019.h"
#include "../../robot/2019/strategy2019Utils.h"
#include "../../robot/2019/strategyConfig2019.h"


// ------------------------------------------------------- NAVIGATIONS ----------------------------------------------------------------

// ------------------------------------------------------ LOCATIONS --------------------------------------------------------------------
// -> General Points
static Location* bigRobotStartAreaLocation;
static Location* acceleratorLocation;

// ------------------------------------------------------- PATHS -------------------------------------------------------------------------

PathData* startArea_to_accelerator_Path;

// ------------------------------------------------------- TARGETS -----------------------------------------------------------------------

// Targets List
static GameTarget acceleratorTarget;
static GameTarget goldeniumTarget;

// ------------------------------------------------------- TARGETS ACTIONS ---------------------------------------------------------------

static GameTargetAction acceleratorTargetAction;
static GameTargetAction goldeniumTargetAction;

// ------------------------------------------------------- TARGETS ACTIONS ITEM LIST --------------------------------------------------------

static GameTargetActionItemList acceleratorTargetActionItemList;
static GameTargetActionItemList goldeniumTargetActionItemList;


// ------------------------------------------------------- TARGET ACTION ITEM LIST ---------------------------------------------------

static GameTargetActionItem acceleratorTargetActionItem;
static GameTargetActionItem goldeniumTargetActionItem;

// ------------------------------------------------------- STRATEGIES ----------------------------------------------------------------

// strategies
// Strategy 0 = Homologation  => No Strategy
// Only Switch
static GameStrategy strategy1;
// Switch + Distributor 1
static GameStrategy strategy2;

// ------------------------------------------------------- STRATEGY ITEM -------------------------------------------------------------

// strategies Items
static GameStrategyItem switchStrategyItem;
static GameStrategyItem distributor1StrategyItem;
static GameStrategyItem borderStrategyItem;
static GameStrategyItem beeStrategyItem;
// static GameStrategyItem distributor2StrategyItem;

// ------------------------------------------------------- INITIALIZATION ------------------------------------------------------------

void initColorAndStartPosition2019(GameStrategyContext* gameStrategyContext) {
    RobotConfig* robotConfig = gameStrategyContext->robotConfig;
    unsigned int configValue = robotConfig->robotConfigReadInt(robotConfig);

    if (configValue & CONFIG_COLOR_YELLOW_MASK) {
        gameStrategyContext->color = TEAM_COLOR_2019_YELLOW;
    }
    else {
        gameStrategyContext->color = TEAM_COLOR_2019_VIOLET;
    }
    float angleDeciDegree = ANGLE_DECI_DEG_90;
    gameStrategyContext->robotPosition->x = BIG_ROBOT_START_AREA_X;
    gameStrategyContext->robotPosition->y = BIG_ROBOT_START_AREA_Y;

    // Symetry
	if (!isViolet(gameStrategyContext)) {
        angleDeciDegree = ANGLE_DECI_DEG_90;
        gameStrategyContext->robotPosition->y = GAMEBOARD_HEIGHT - gameStrategyContext->robotPosition->y;
	}
    float angleRadian = deciDegreeToRad(angleDeciDegree);
    gameStrategyContext->robotAngleRadian = angleRadian;
}

Location* addNavigationWithColors(enum TeamColor teamColor, Navigation* navigation, char* name, float x, float y) {
    LocationList* locationList = navigation->locationList;
    if (teamColor == TEAM_COLOR_2019_VIOLET) {
        y = GAMEBOARD_HEIGHT - y;
    }
    Location* result = addNamedLocation(locationList, name, x, y);
    return result;
}


void initLocations2019(GameStrategyContext* gameStrategyContext) {
    Navigation* navigation = gameStrategyContext->navigation;
    enum TeamColor teamColor = gameStrategyContext->color;
    bigRobotStartAreaLocation = addNavigationWithColors(teamColor, navigation, BIG_ROBOT_START_AREA, BIG_ROBOT_START_AREA_X, BIG_ROBOT_START_AREA_Y);

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

void initPaths2019(GameStrategyContext* gameStrategyContext, int index) {
    /*
    Navigation* navigation = gameStrategyContext->navigation;
    
    RobotConfig* robotConfig = gameStrategyContext->robotConfig;
    enum TeamColor teamColor = gameStrategyContext->color;
    float aFactor = getAccelerationFactor(robotConfig);
    float speedFactor = getSpeedFactor(robotConfig);
    
    startArea_to_accelerator_Path = addNavigationPathWithColor(teamColor,
                                                 navigation,
                                                 bigRobotStartAreaLocation, 
                                                 acceleratorLocation,
                                                 DEFAULT_NAVIGATION_COST,
                                                 STARTAREA_TO_ACCELERATOR_CP1, 
                                                 STARTAREA_TO_ACCELERATOR_CP2,
                                                 deciDegreeToRad(BIG_ROBOT_START_AREA_ANGLE_DECI_DEG),
                                                 deciDegreeToRad(ACCELERATOR_AN SWITCH_ANGLE_DECI_DEG),
                                                 aFactor * STARTAREA_TO_SWITCH_ACCELERATION_FACTOR,
                                                 speedFactor * STARTAREA_TO_SWITCH_SPEED_FACTOR);
                                                 */
}

void initTargets2019(GameStrategyContext* gameStrategyContext) {
	clearGameTargets();

    // addGameTarget(&switchTarget, "SWITCH_TARGET", SCORE_POINT_2018_PANEL_ON_POINT, switchLocation);
}

void initTargetActions2019(GameStrategyContext* gameStrategyContext) {
    // SWITCH
    // addTargetAction(&(switchTarget.actionList), &switchTargetAction, switchLocation, switchLocation, ACTION_SWITCH_TIME_TO_ACHIEVE, NULL, &switchTargetActionItemList);
}

void initTargetActionsItems2019(GameStrategyContext* gameStrategyContext) {
    // addTargetActionItem(&switchTargetActionItemList, &switchTargetActionItem, &switch2018On, "SWITCH ON");
}

/**
* @private.
*/
void initStrategies2019(GameStrategyContext* gameStrategyContext) {
	clearGameStrategies();
	addGameStrategy(&strategy1, "ACCELERATOR");
}

GameStrategy* initStrategiesItems2019(GameStrategyContext* gameStrategyContext) {
    // We only load the item relative to the strategy Index chosen
    if (gameStrategyContext->strategyIndex == NO_STRATEGY_INDEX) {
        return NULL;
    }
    if (gameStrategyContext->strategyIndex == STRATEGY_1_SIMPLE_PUCK) {
        // addGameStrategyItem(&strategy1, &switchStrategyItem, &switchTarget);
        return &strategy1;
    }
    if (gameStrategyContext->strategyIndex == STRATEGY_2_ACCELERATOR) {
        addGameStrategyItem(&strategy2, &switchStrategyItem, &acceleratorTarget);
        return &strategy2;
    }
    return NULL;
}

void initStrategy2019(GameStrategyContext* gameStrategyContext) {
    initColorAndStartPosition2019(gameStrategyContext);
    float tofDistanceFactor = getSonarDistanceCheckFactor(gameStrategyContext->robotConfig);
    setTofListOrientationAngle(gameStrategyContext->tofSensorList, tofDistanceFactor);
    showGameStrategyContextTeamColorAndStrategy(gameStrategyContext);

	initLocations2019(gameStrategyContext);
	initPaths2019(gameStrategyContext, gameStrategyContext->strategyIndex);

	initTargets2019(gameStrategyContext);
	initTargetActions2019(gameStrategyContext);
	initTargetActionsItems2019(gameStrategyContext);

	initStrategies2019(gameStrategyContext);
	

	GameStrategy* strategy = initStrategiesItems2019(gameStrategyContext);
    gameStrategyContext->gameStrategy = strategy;
    gameStrategyContext->maxTargetToHandle = getGameTargetList()->size;

	// opponent
	Point* p = gameStrategyContext->opponentRobotPosition;
	p->x = 0;
	p->y = 0;

	// obstacle
	p = gameStrategyContext->lastObstaclePosition;
	p->x = 0;
	p->y = 0;

    gameStrategyContext->hasMoreNextSteps = true;

	// reinitialize the game board to change elements / targets ...
}
