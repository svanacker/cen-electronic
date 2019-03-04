#include <stdlib.h>

#include "strategy2018.h"
#include "strategyConfig2018.h"
#include "strategyAction2018.h"
#include "strategy2018Utils.h"

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

#include "../../client/robot/2018/launcherClient2018.h"

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

#include "../../robot/2018/launcherDeviceInterface2018.h"
#include "../../robot/2018/teamColor2018.h"

// ------------------------------------------------------- NAVIGATIONS ----------------------------------------------------------------

// ------------------------------------------------------ LOCATIONS --------------------------------------------------------------------
// -> General Points
static Location* startAreaLocation;
static Location* switchLocation;
static Location* distributor1Location;
static Location* beeBorderAlignYLocation;
static Location* beeLocation;
static Location* distributor2FrontLocation;
static Location* distributor2Location;
static Location* garbageFrontLocation;
static Location* garbageReleaseLocation;

// Building points
/*
static Location* buildingAreaLocation;
static Location* buildingLeft1Location;
static Location* buildingLeft2Location;
static Location* buildingMiddle1Location;
static Location* buildingMiddle2Location;
static Location* buildingRight1Location;
static Location* buildingRight2Location;
*/
// ------------------------------------------------------- PATHS -------------------------------------------------------------------------

PathData* startArea_to_switch_Path;
PathData* switch_to_distributor1_Path;
PathData* distributor1_to_beeBorderAlignY_Path;
PathData* beeBorderAlignY_to_bee_Path;
PathData* bee_to_distributor2Front_Path;
PathData* distributor2Front_to_distributor2_Path;
PathData* distributor2_to_garbageFront_Path;
PathData* garbageFront_to_garbageRelease_Path;

// ------------------------------------------------------- TARGETS -----------------------------------------------------------------------

// Targets List
static GameTarget switchTarget;
static GameTarget distributor1Target;
static GameTarget borderTarget;
static GameTarget beeTarget;
static GameTarget distributor2Target;
static GameTarget garbageTarget;
// TODO : static GameTarget unloadDistributor2GameTarget;

// ------------------------------------------------------- TARGETS ACTIONS ---------------------------------------------------------------

static GameTargetAction switchTargetAction;
static GameTargetAction borderTargetAction;
static GameTargetAction distributor1TargetAction;
static GameTargetAction beeTargetAction;
static GameTargetAction distributor2TargetAction;

// ------------------------------------------------------- TARGETS ACTIONS ITEM LIST --------------------------------------------------------

static GameTargetActionItemList switchTargetActionItemList;
static GameTargetActionItemList distributor1TargetActionItemList;
static GameTargetActionItemList borderTargetActionItemList;
static GameTargetActionItemList beeTargetActionItemList;
static GameTargetActionItemList distributor2TargetActionItemList;


// ------------------------------------------------------- TARGET ACTION ITEM LIST ---------------------------------------------------

static GameTargetActionItem switchTargetActionItem;
static GameTargetActionItem distributor1TargetActionItem;
// No static GameTargetActionItem borderTargetActionItem;
// No static GameTargetActionItem beeTargetActionItem;
static GameTargetActionItem distributor2TargetActionItem;

// ------------------------------------------------------- STRATEGIES ----------------------------------------------------------------

// strategies
// Strategy 0 = Homologation  => No Strategy
// Only Switch
static GameStrategy strategy1;
// Switch + Distributor 1
static GameStrategy strategy2;

// Switch + Distributor 1 + Bee
static GameStrategy strategy3;

// Switch + Distributor 1 + Bee + Distributor 2
static GameStrategy strategy4;

// Switch + Bee
static GameStrategy strategy5;

// ------------------------------------------------------- STRATEGY ITEM -------------------------------------------------------------

// strategies Items
static GameStrategyItem switchStrategyItem;
static GameStrategyItem distributor1StrategyItem;
static GameStrategyItem borderStrategyItem;
static GameStrategyItem beeStrategyItem;
// static GameStrategyItem distributor2StrategyItem;

// ------------------------------------------------------- INITIALIZATION ------------------------------------------------------------

void initColorAndStartPosition2018(GameStrategyContext* gameStrategyContext) {
    RobotConfig* robotConfig = gameStrategyContext->robotConfig;
    unsigned int configValue = robotConfig->robotConfigReadInt(robotConfig);

    if (configValue & CONFIG_COLOR_YELLOW_MASK) {
        gameStrategyContext->color = TEAM_COLOR_2018_GREEN;
    }
    else {
        gameStrategyContext->color = TEAM_COLOR_2018_ORANGE;
    }
    float angleDeciDegree = ANGLE_DECI_DEG_270;
    gameStrategyContext->robotPosition->x = START_AREA_X;
    gameStrategyContext->robotPosition->y = START_AREA_Y;

    // Symetry
	if (!isGreen(gameStrategyContext)) {
        angleDeciDegree = ANGLE_DECI_DEG_90;
        gameStrategyContext->robotPosition->y = GAMEBOARD_HEIGHT - gameStrategyContext->robotPosition->y;
	}
    float angleRadian = deciDegreeToRad(angleDeciDegree);
    gameStrategyContext->robotAngleRadian = angleRadian;
}

Location* addNavigationWithColors(enum TeamColor teamColor, Navigation* navigation, char* name, float x, float y) {
    LocationList* locationList = navigation->locationList;
    if (teamColor == TEAM_COLOR_2018_ORANGE) {
        y = GAMEBOARD_HEIGHT - y;
    }
    Location* result = addNamedLocation(locationList, name, x, y);
    return result;
}


void initLocations2018(GameStrategyContext* gameStrategyContext) {
    Navigation* navigation = gameStrategyContext->navigation;
    enum TeamColor teamColor = gameStrategyContext->color;
    startAreaLocation = addNavigationWithColors(teamColor, navigation, START_AREA, START_AREA_X, START_AREA_Y);

    // Switch
    switchLocation = addNavigationWithColors(teamColor, navigation, SWITCH, SWITCH_X, SWITCH_Y);

    // Distributor 1
    distributor1Location = addNavigationWithColors(teamColor, navigation, DISTRIBUTOR_1, DISTRIBUTOR_1_X, DISTRIBUTOR_1_Y);

    // Bee Border
    beeBorderAlignYLocation = addNavigationWithColors(teamColor, navigation, BEE_BORDER_Y_ALIGN, BEE_BORDER_Y_ALIGN_X, BEE_BORDER_Y_ALIGN_Y);
    
    // Bee
    beeLocation = addNavigationWithColors(teamColor, navigation, BEE, BEE_X, BEE_Y);

    // Distributor 2
    distributor2FrontLocation = addNavigationWithColors(teamColor, navigation, DISTRIBUTOR_2_FRONT, DISTRIBUTOR_2_FRONT_X, DISTRIBUTOR_2_FRONT_Y);
    distributor2Location = addNavigationWithColors(teamColor, navigation, DISTRIBUTOR_2, DISTRIBUTOR_2_X, DISTRIBUTOR_2_Y);

    // Garbage
    garbageFrontLocation = addNavigationWithColors(teamColor, navigation, GARBAGE_FRONT, GARBAGE_FRONT_POINT_X, GARBAGE_FRONT_POINT_Y);
    garbageReleaseLocation = addNavigationWithColors(teamColor, navigation, GARBAGE_RELEASE, GARBAGE_RELEASE_POINT_X, GARBAGE_RELEASE_POINT_Y);
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

    if (teamColor == TEAM_COLOR_2018_ORANGE) {
        angle1 = mod2PI(-angle1);
        angle2 = mod2PI(-angle2);
    }

    initPathData(pathData, location1, location2, cost, controlPointDistance1, controlPointDistance2, angle1, angle2, accelerationFactor, speedFactor);
    return pathData;
}

void initPaths2018(GameStrategyContext* gameStrategyContext, int index) {
    Navigation* navigation = gameStrategyContext->navigation;
    
    RobotConfig* robotConfig = gameStrategyContext->robotConfig;
    enum TeamColor teamColor = gameStrategyContext->color;
    float aFactor = getAccelerationFactor(robotConfig);
    float speedFactor = getSpeedFactor(robotConfig);
    
    startArea_to_switch_Path = addNavigationPathWithColor(teamColor,
                                                 navigation,
                                                 startAreaLocation, 
                                                 switchLocation,
                                                 DEFAULT_NAVIGATION_COST,
                                                 STARTAREA_TO_SWITCH_CP1, 
                                                 STARTAREA_TO_SWITCH_CP2,
                                                 deciDegreeToRad(START_AREA_ANGLE_DECI_DEG),
                                                 deciDegreeToRad(SWITCH_ANGLE_DECI_DEG),
                                                 aFactor * STARTAREA_TO_SWITCH_ACCELERATION_FACTOR,
                                                 speedFactor * STARTAREA_TO_SWITCH_SPEED_FACTOR);
    switch_to_distributor1_Path = addNavigationPathWithColor(teamColor,
                                                    navigation,
                                                    switchLocation,
                                                    distributor1Location,
                                                    DEFAULT_NAVIGATION_COST,
                                                    SWITCH_TO_DISTRIBUTOR_1_CP1, 
                                                    SWITCH_TO_DISTRIBUTOR_1_CP2,
                                                    deciDegreeToRad(SWITCH_ANGLE_DECI_DEG),
                                                    deciDegreeToRad(DISTRIBUTOR_1_ANGLE_DECI_DEG),
                                                    aFactor * SWITCH_TO_DISTRIBUTOR_1_ACCELERATION_FACTOR,
                                                    speedFactor * SWITCH_TO_DISTRIBUTOR_1_SPEED_FACTOR);

    distributor1_to_beeBorderAlignY_Path = addNavigationPathWithColor(teamColor,
                                                             navigation,
                                                             distributor1Location,
                                                             beeBorderAlignYLocation,
                                                             DEFAULT_NAVIGATION_COST,
                                                             DISTRIBUTOR_1_TO_BEE_BORDER_ALIGN_Y_CP1,
                                                             DISTRIBUTOR_1_TO_BEE_BORDER_ALIGN_Y_CP2,
                                                             deciDegreeToRad(DISTRIBUTOR_1_ANGLE_DECI_DEG),
                                                             deciDegreeToRad(BEE_BORDER_Y_ALIGN_ANGLE_DECI_DEG),
                                                             aFactor * DISTRIBUTOR_1_TO_BEE_BORDER_ALIGN_Y_COST_ACCELERATION_FACTOR,
                                                             speedFactor * DISTRIBUTOR_1_TO_BEE_BORDER_ALIGN_Y_COST_SPEED_FACTOR);

    beeBorderAlignY_to_bee_Path = addNavigationPathWithColor(teamColor,
                                                             navigation,
                                                             beeBorderAlignYLocation,
                                                             beeLocation,
                                                             DEFAULT_NAVIGATION_COST,
                                                             BEE_BORDER_ALIGN_Y_TO_BEE_CP1,
                                                             BEE_BORDER_ALIGN_Y_TO_BEE_CP2,
                                                             deciDegreeToRad(BEE_BORDER_Y_ALIGN_ANGLE_DECI_DEG),
                                                             deciDegreeToRad(BEE_ANGLE_DECI_DEG),
                                                             aFactor * BEE_BORDER_ALIGN_Y_TO_BEE_ACCELERATION_FACTOR,
                                                             speedFactor * BEE_BORDER_ALIGN_Y_TO_BEE_SPEED_FACTOR);
    bee_to_distributor2Front_Path = addNavigationPathWithColor(teamColor,
                                                             navigation,
                                                             beeLocation,
                                                             distributor2FrontLocation,
                                                             DEFAULT_NAVIGATION_COST,
                                                             BEE_TO_DISTRIBUTOR_2_FRONT_CP1,
                                                             BEE_TO_DISTRIBUTOR_2_FRONT_CP2,
                                                             deciDegreeToRad(BEE_ANGLE_DECI_DEG),
                                                             deciDegreeToRad(DISTRIBUTOR_2_FRONT_ANGLE_DECI_DEG),
                                                             aFactor * BEE_TO_DISTRIBUTOR_2_FRONT_ACCELERATION_FACTOR,
                                                             speedFactor * BEE_TO_DISTRIBUTOR_2_FRONT_SPEED_FACTOR);
                                                             
    distributor2Front_to_distributor2_Path = addNavigationPathWithColor(teamColor,
                                                             navigation,
                                                             distributor2FrontLocation,
                                                             distributor2Location,
                                                             DEFAULT_NAVIGATION_COST,
                                                             DISTRIBUTOR_2_FRONT_TO_DISTRIBUTOR_2_CP1,
                                                             DISTRIBUTOR_2_FRONT_TO_DISTRIBUTOR_2_CP2,
                                                             deciDegreeToRad(DISTRIBUTOR_2_FRONT_ANGLE_DECI_DEG),
                                                             deciDegreeToRad(DISTRIBUTOR_2_ANGLE_DECI_DEG),
                                                             aFactor * DISTRIBUTOR_2_FRONT_TO_DISTRIBUTOR_2_ACCELERATION_FACTOR,
                                                             speedFactor * DISTRIBUTOR_2_FRONT_TO_DISTRIBUTOR_2_SPEED_FACTOR);
                                                             
     distributor2_to_garbageFront_Path = addNavigationPathWithColor(teamColor,
                                                             navigation,
                                                             distributor2Location,
                                                             garbageFrontLocation,
                                                             DEFAULT_NAVIGATION_COST,
                                                             DISTRIBUTOR_2_TO_GARBAGE_FRONT_CP1,
                                                             DISTRIBUTOR_2_TO_GARBAGE_FRONT_CP2,
                                                             deciDegreeToRad(DISTRIBUTOR_2_ANGLE_DECI_DEG),
                                                             deciDegreeToRad(GARGAGE_FRONT_POINT_ANGLE_DECI_DEG),
                                                             aFactor * DISTRIBUTOR_2_TO_GARBAGE_FRONT_ACCELERATION_FACTOR,
                                                             speedFactor * DISTRIBUTOR_2_TO_GARBAGE_FRONT_SPEED_FACTOR);
                                                             
     garbageFront_to_garbageRelease_Path = addNavigationPathWithColor(teamColor,
                                                             navigation,
                                                             garbageFrontLocation,
                                                             garbageReleaseLocation,
                                                             DEFAULT_NAVIGATION_COST,
                                                             GARBAGE_FRONT_TO_GARBAGE_RELEASE_CP1,
                                                             GARBAGE_FRONT_TO_GARBAGE_RELEASE_CP2,
                                                             deciDegreeToRad(GARGAGE_RELEASE_POINT_ANGLE_DECI_DEG),
                                                             deciDegreeToRad(GARGAGE_RELEASE_POINT_ANGLE_DECI_DEG),
                                                             GARBAGE_FRONT_TO_GARBAGE_RELEASE_ACCELERATION_FACTOR,
                                                             GARBAGE_FRONT_TO_GARBAGE_RELEASE_SPEED_FACTOR);
}

void initTargets2018(GameStrategyContext* gameStrategyContext) {
	clearGameTargets();

    addGameTarget(&switchTarget, "SWITCH_TARGET", SCORE_POINT_2018_PANEL_ON_POINT, switchLocation);
    addGameTarget(&distributor1Target, "DIST_1", SCORE_POINT_2018_DISTRIBUTOR_UNICOLOR_COMPLETE_POINT, distributor1Location);
    addGameTarget(&borderTarget, "BORDER", SCORE_POINT_2018_NO_POINT, beeBorderAlignYLocation);
    addGameTarget(&beeTarget, "BEE", SCORE_POINT_2018_BEE_DESTROYED_POINT, beeLocation);
    addGameTarget(&distributor2Target, "DIST_2_LOAD", SCORE_POINT_2018_DISTRIBUTOR_UNLOADED_POINT, distributor2Location);
    addGameTarget(&garbageTarget, "GARBAGE_RELEASE", SCORE_POINT_2018_GARBAGE_RELEASE_POINT, garbageReleaseLocation);
}

void initTargetActions2018(GameStrategyContext* gameStrategyContext) {
    // SWITCH
    addTargetAction(&(switchTarget.actionList), &switchTargetAction, switchLocation, switchLocation, ACTION_SWITCH_TIME_TO_ACHIEVE, NULL, &switchTargetActionItemList);
    // DISTRIBUTOR 1
    addTargetAction(&(distributor1Target.actionList), &distributor1TargetAction, distributor1Location, distributor1Location, ACTION_DISTRIBUTOR_1_TIME_TO_ACHIEVE, NULL, &distributor1TargetActionItemList);
    // BORDER
    addTargetAction(&(borderTarget.actionList), &borderTargetAction, beeBorderAlignYLocation, beeBorderAlignYLocation, ACTION_TIME_NO_ACTION, NULL, &borderTargetActionItemList);
    // BEE
    addTargetAction(&(beeTarget.actionList), &beeTargetAction, beeLocation, beeLocation, ACTION_BEE_TIME_TO_ACHIEVE, NULL, &beeTargetActionItemList);
    // DISTRIBUTOR 2
    addTargetAction(&(distributor2Target.actionList), &distributor2TargetAction, distributor2Location, distributor2Location, ACTION_DISTRIBUTOR_2_TIME_TO_ACHIEVE, NULL, &distributor2TargetActionItemList);
}

void initTargetActionsItems2018(GameStrategyContext* gameStrategyContext) {
    addTargetActionItem(&switchTargetActionItemList, &switchTargetActionItem, &switch2018On, "SWITCH ON");
    addTargetActionItem(&distributor1TargetActionItemList, &distributor1TargetActionItem, &distributor1_2018, "DIST_1");
//    addTargetActionItem(&beeTargetActionItemList, &beeTargetActionItem, &bee2018, "BEE");
    addTargetActionItem(&distributor2TargetActionItemList, &distributor2TargetActionItem, &distributor2_2018, "DIST_2");
}

/**
* @private.
*/
void initStrategies2018(GameStrategyContext* gameStrategyContext) {
	clearGameStrategies();
	addGameStrategy(&strategy1, "SWITCH");
    addGameStrategy(&strategy2, "SW_DIST");
    addGameStrategy(&strategy3, "SW_DIST_BEE");
    addGameStrategy(&strategy4, "SW_DIST_BEE_DIST");
    addGameStrategy(&strategy5, "SW_BEE");
}

GameStrategy* initStrategiesItems2018(GameStrategyContext* gameStrategyContext) {
    // We only load the item relative to the strategy Index chosen
    if (gameStrategyContext->strategyIndex == NO_STRATEGY_INDEX) {
        return NULL;
    }
    if (gameStrategyContext->strategyIndex == STRATEGY_1_SWITCH_INDEX) {
        addGameStrategyItem(&strategy1, &switchStrategyItem, &switchTarget);
        return &strategy1;
    }
    if (gameStrategyContext->strategyIndex == STRATEGY_2_SWITCH_DIST_INDEX) {
        addGameStrategyItem(&strategy2, &switchStrategyItem, &switchTarget);
        addGameStrategyItem(&strategy2, &distributor1StrategyItem, &distributor1Target);
        return &strategy2;
    }
    if (gameStrategyContext->strategyIndex == STRATEGY_3_SWITCH_DIST_BEE_INDEX) {
        addGameStrategyItem(&strategy3, &switchStrategyItem, &switchTarget);
        addGameStrategyItem(&strategy3, &distributor1StrategyItem, &distributor1Target);
        addGameStrategyItem(&strategy3, &borderStrategyItem, &borderTarget);
        addGameStrategyItem(&strategy3, &beeStrategyItem, &beeTarget);
        return &strategy3;
    }
    /*
    if (gameStrategyContext->strategyIndex == STRATEGY_4_SWITCH_DIST_BEE_DIST_INDEX) {
        addGameStrategyItem(&strategy4, &switchStrategyItem, &switchTarget);
        addGameStrategyItem(&strategy4, &distributor1StrategyItem, &distributor1Target);
        addGameStrategyItem(&strategy4, &beeStrategyItem, &beeTarget);
        addGameStrategyItem(&strategy4, &distributor2StrategyItem, &distributor2Target);
        return &strategy4;
    }
    if (gameStrategyContext->strategyIndex == STRATEGY_5_SWITCH_BEE_INDEX) {
        addGameStrategyItem(&strategy5, &switchStrategyItem, &switchTarget);
        addGameStrategyItem(&strategy5, &beeStrategyItem, &beeTarget);
        return &strategy5;
    }
    */
    return NULL;
}

void initStrategy2018(GameStrategyContext* gameStrategyContext) {
    initColorAndStartPosition2018(gameStrategyContext);
    float tofDistanceFactor = getSonarDistanceCheckFactor(gameStrategyContext->robotConfig);
    setTofListOrientationAngle(gameStrategyContext->tofSensorList, tofDistanceFactor);
    showGameStrategyContextTeamColorAndStrategy(gameStrategyContext);

	initLocations2018(gameStrategyContext);
	initPaths2018(gameStrategyContext, gameStrategyContext->strategyIndex);

	initTargets2018(gameStrategyContext);
	initTargetActions2018(gameStrategyContext);
	initTargetActionsItems2018(gameStrategyContext);

	initStrategies2018(gameStrategyContext);
	

	GameStrategy* strategy = initStrategiesItems2018(gameStrategyContext);
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
