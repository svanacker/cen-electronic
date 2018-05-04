#include <stdlib.h>

#include "strategy2018.h"
#include "strategy2018Utils.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../motion/motion.h"
#include "../../motion/simple/simpleMotion.h"
#include "../../motion/extended/bsplineMotion.h"

#include "../../navigation/locationList.h"
#include "../../navigation/path.h"
#include "../../navigation/pathList.h"
#include "../../navigation/pathListDebug.h"
#include "../../navigation/navigation.h"

#include "../../robot/gameboard/gameBoard.h"


#include "../../robot/strategy/gameStrategy.h"
#include "../../robot/strategy/gameStrategyHandler.h"
#include "../../robot/strategy/gameStrategyList.h"
#include "../../robot/strategy/gameTargetList.h"
#include "../../robot/strategy/gameTarget.h"
#include "../../robot/strategy/gameTargetAction.h"
#include "../../robot/strategy/gameTargetActionItem.h"
#include "../../robot/strategy/gameTargetActionList.h"

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
static GameTarget distributor1GameTarget;
static GameTarget beeTarget;
static GameTarget distributor2GameTarget;
static GameTarget garbageTarget;
// TODO : static GameTarget unloadDistributor2GameTarget;

// ------------------------------------------------------- TARGETS ACTIONS ---------------------------------------------------------------

// static GameTargetAction distributor1TakeTargetAction;

// ------------------------------------------------------- TARGETS ACTIONS ITEMS --------------------------------------------------------

// static GameTargetActionItemList distributor1TakeTargetActionItemList;

// ------------------------------------------------------- STRATEGIES ----------------------------------------------------------------

// strategies
static GameStrategy strategy1;

// strategies Items
// static GameStrategyItem distributor1StrategyItem;

// ------------------------------------------------------- INITIALIZATION ------------------------------------------------------------

void setColor(GameStrategyContext* gameStrategyContext, enum TeamColor color) {
	appendStringAndDec(getInfoOutputStreamLogger(), "setColor:", color);
	println(getInfoOutputStreamLogger());

    gameStrategyContext->color = color;
	// changeLocationsForColor();
	float angle = ANGLE_180;
    gameStrategyContext->robotPosition->x = START_AREA_X;
    gameStrategyContext->robotPosition->y = START_AREA_Y;
    // Symetry
	if (!isGreen(gameStrategyContext)) {
		angle = -angle;
        gameStrategyContext->robotPosition->y = GAMEBOARD_HEIGHT - gameStrategyContext->robotPosition->y;
	}

    gameStrategyContext->robotAngle = angle;

	printStrategyAllDatas(gameStrategyContext, getInfoOutputStreamLogger());
}

void initLocations2018(GameStrategyContext* gameStrategyContext) {
    Navigation* navigation = gameStrategyContext->navigation;
    startAreaLocation = addNavigationLocation(navigation, START_AREA, START_AREA_X, START_AREA_Y);

    // Switch
    switchLocation = addNavigationLocation(navigation, SWITCH, SWITCH_X, SWITCH_Y);

    // Distributor 1
    distributor1Location = addNavigationLocation(navigation, DISTRIBUTOR_1, DISTRIBUTOR_1_X, DISTRIBUTOR_1_Y);

    // Bee
    beeBorderAlignYLocation = addNavigationLocation(navigation, BEE_BORDER_Y_ALIGN, BEE_BORDER_Y_ALIGN_X, BEE_BORDER_Y_ALIGN_Y);
    beeLocation = addNavigationLocation(navigation, BEE, BEE_X, BEE_Y);

    // Distributor 2
    distributor2FrontLocation = addNavigationLocation(navigation, DISTRIBUTOR_2_FRONT, DISTRIBUTOR_2_FRONT_X, DISTRIBUTOR_2_FRONT_Y);
    distributor2Location = addNavigationLocation(navigation, DISTRIBUTOR_2, DISTRIBUTOR_2_X, DISTRIBUTOR_2_Y);

    // Garbage
    garbageFrontLocation = addNavigationLocation(navigation, GARBAGE_FRONT, GARBAGE_FRONT_POINT_X, GARBAGE_FRONT_POINT_Y);
    garbageReleaseLocation = addNavigationLocation(navigation, GARBAGE_RELEASE, GARBAGE_RELEASE_POINT_X, GARBAGE_RELEASE_POINT_Y);

}

void initPaths2018(GameStrategyContext* gameStrategyContext, int index) {
    Navigation* navigation = gameStrategyContext->navigation;
    startArea_to_switch_Path = addNavigationPath(navigation,
                                                 startAreaLocation, 
                                                 switchLocation,
                                                 DEFAULT_NAVIGATION_COST,
                                                 STARTAREA_TO_SWITCH_CP1, 
                                                 STARTAREA_TO_SWITCH_CP2,
                                                 START_AREA_ANGLE,
                                                 SWITCH_ANGLE,
                                                 STARTAREA_TO_SWITCH_ACCELERATION_FACTOR,
                                                 STARTAREA_TO_SWITCH_SPEED_FACTOR);
        
    switch_to_distributor1_Path = addNavigationPath(navigation,
                                                    switchLocation,
                                                    distributor1Location,
                                                    DEFAULT_NAVIGATION_COST,
                                                    SWITCH_TO_DISTRIBUTOR_1_CP1, 
                                                    SWITCH_TO_DISTRIBUTOR_1_CP2,
                                                    SWITCH_ANGLE,
                                                    DISTRIBUTOR_1_ANGLE,
                                                    SWITCH_TO_DISTRIBUTOR_1_ACCELERATION_FACTOR,
                                                    SWITCH_TO_DISTRIBUTOR_1_SPEED_FACTOR);

    distributor1_to_beeBorderAlignY_Path = addNavigationPath(navigation,
                                                             distributor1Location,
                                                             beeBorderAlignYLocation,
                                                             DEFAULT_NAVIGATION_COST,
                                                             DISTRIBUTOR_1_TO_BEE_BORDER_ALIGN_Y_CP1,
                                                             DISTRIBUTOR_1_TO_BEE_BORDER_ALIGN_Y_CP2,
                                                             DISTRIBUTOR_1_ANGLE,
                                                             BEE_BORDER_Y_ALIGN_ANGLE,
                                                             DISTRIBUTOR_1_TO_BEE_BORDER_ALIGN_Y_COST_ACCELERATION_FACTOR,
                                                             DISTRIBUTOR_1_TO_BEE_BORDER_ALIGN_Y_COST_SPEED_FACTOR);

    beeBorderAlignY_to_bee_Path = addNavigationPath(navigation,
                                                             beeBorderAlignYLocation,
                                                             beeLocation,
                                                             DEFAULT_NAVIGATION_COST,
                                                             BEE_BORDER_ALIGN_Y_TO_BEE_CP1,
                                                             BEE_BORDER_ALIGN_Y_TO_BEE_CP2,
                                                             BEE_BORDER_Y_ALIGN_ANGLE,
                                                             BEE_ANGLE,
                                                             BEE_BORDER_ALIGN_Y_TO_BEE_ACCELERATION_FACTOR,
                                                             BEE_BORDER_ALIGN_Y_TO_BEE_SPEED_FACTOR);

    bee_to_distributor2Front_Path = addNavigationPath(navigation,
                                                             beeLocation,
                                                             distributor2FrontLocation,
                                                             DEFAULT_NAVIGATION_COST,
                                                             BEE_TO_DISTRIBUTOR_2_FRONT_CP1,
                                                             BEE_TO_DISTRIBUTOR_2_FRONT_CP2,
                                                             BEE_ANGLE,
                                                             DISTRIBUTOR_2_FRONT_ANGLE,
                                                             BEE_TO_DISTRIBUTOR_2_FRONT_ACCELERATION_FACTOR,
                                                             BEE_TO_DISTRIBUTOR_2_FRONT_SPEED_FACTOR);

    distributor2Front_to_distributor2_Path = addNavigationPath(navigation,
                                                             distributor2FrontLocation,
                                                             distributor2Location,
                                                             DEFAULT_NAVIGATION_COST,
                                                             DISTRIBUTOR_2_FRONT_TO_DISTRIBUTOR_2_CP1,
                                                             DISTRIBUTOR_2_FRONT_TO_DISTRIBUTOR_2_CP2,
                                                             DISTRIBUTOR_2_FRONT_ANGLE,
                                                             DISTRIBUTOR_2_ANGLE,
                                                             DISTRIBUTOR_2_FRONT_TO_DISTRIBUTOR_2_ACCELERATION_FACTOR,
                                                             DISTRIBUTOR_2_FRONT_TO_DISTRIBUTOR_2_SPEED_FACTOR);

     distributor2_to_garbageFront_Path = addNavigationPath(navigation,
                                                             distributor2Location,
                                                             garbageFrontLocation,
                                                             DEFAULT_NAVIGATION_COST,
                                                             DISTRIBUTOR_2_TO_GARBAGE_FRONT_CP1,
                                                             DISTRIBUTOR_2_TO_GARBAGE_FRONT_CP2,
                                                             DISTRIBUTOR_2_ANGLE,
                                                             GARGAGE_FRONT_POINT_ANGLE,
                                                             DISTRIBUTOR_2_TO_GARBAGE_FRONT_ACCELERATION_FACTOR,
                                                             DISTRIBUTOR_2_TO_GARBAGE_FRONT_SPEED_FACTOR);

     garbageFront_to_garbageRelease_Path = addNavigationPath(navigation,
                                                             garbageFrontLocation,
                                                             garbageReleaseLocation,
                                                             DEFAULT_NAVIGATION_COST,
                                                             GARBAGE_FRONT_TO_GARBAGE_RELEASE_CP1,
                                                             GARBAGE_FRONT_TO_GARBAGE_RELEASE_CP2,
                                                             GARGAGE_FRONT_POINT_ANGLE,
                                                             GARGAGE_RELEASE_POINT_ANGLE,
                                                             GARBAGE_FRONT_TO_GARBAGE_RELEASE_ACCELERATION_FACTOR,
                                                             GARBAGE_FRONT_TO_GARBAGE_RELEASE_SPEED_FACTOR);
}

void initTargets2018(GameStrategyContext* gameStrategyContext) {
	clearGameTargets();

    addGameTarget(&switchTarget, "SWITCH_TARGET", POINT_2018_PANEL_ON_POINT, switchLocation);
    addGameTarget(&distributor1GameTarget, "DIST_1", POINT_2018_DISTRIBUTOR_UNICOLOR_COMPLETE_POINT, distributor1Location);
    addGameTarget(&beeTarget, "BEE", POINT_2018_BEE_DESTROYED_POINT, beeLocation);
    addGameTarget(&distributor2GameTarget, "DIST_2_LOAD", POINT_2018_DISTRIBUTOR_UNLOADED_POINT, distributor2Location);
    addGameTarget(&garbageTarget, "GARBAGE_RELEASE", POINT_2018_GARBAGE_RELEASE_POINT, garbageReleaseLocation);
}

void initTargetActions2018(GameStrategyContext* gameStrategyContext) {

}

void initTargetActionsItems2018(GameStrategyContext* gameStrategyContext) {
}

/**
* @private.
*/
void initStrategies2018(GameStrategyContext* gameStrategyContext) {
	clearGameStrategies();
	addGameStrategy(&strategy1, "S1");
}

void initStrategiesItems2018(GameStrategyContext* gameStrategyContext, int strategyIndex) {
//	addGameStrategyItem(&strategy1, &distributor1StrategyItem, );
}

void initStrategy2018(GameStrategyContext* gameStrategyContext, int strategyIndex) {

	initLocations2018(gameStrategyContext);
	initPaths2018(gameStrategyContext, strategyIndex);

	initTargets2018(gameStrategyContext);
	initTargetActions2018(gameStrategyContext);
	initTargetActionsItems2018(gameStrategyContext);

	initStrategies2018(gameStrategyContext);
	initStrategiesItems2018(gameStrategyContext, strategyIndex);

	GameStrategy* strategy = getGameStrategy(0);
    gameStrategyContext->gameStrategy = strategy;
    gameStrategyContext->maxTargetToHandle = getGameTargetList()->size;

	//OutputStream* debugOutputStream = getInfoOutputStreamLogger();
	//printStrategyAllDatas(debugOutputStream);

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

void printStrategyAllDatas(GameStrategyContext* gameStrategyContext, OutputStream* outputStream) {
    // Navigation* navigation = gameStrategyContext->navigation;
    /*
	printLocationListTable(outputStream, navigation->locationList);
	printPathListTable(outputStream, navigation->paths);
	printGameTargetList(outputStream);
	printGameStrategyTableList(outputStream);
	printGameStrategyContext(outputStream, gameStrategyContext);
    */
}
