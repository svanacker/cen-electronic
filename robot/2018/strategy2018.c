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

#define STRATEGY_2018_NAVIGATION_LOCATION_LIST_ARRAY_LENGTH        30
#define STRATEGY_2018_NAVIGATION_PATH_LIST_TEST_ARRAY_LENGTH       30
#define STRATEGY_2018_BIT_LIST_NAVIGATION_TEST_ARRAY_LENGTH        30

static LocationList locationList;
static Location locationListArray[STRATEGY_2018_NAVIGATION_LOCATION_LIST_ARRAY_LENGTH];

static PathList pathList;
static PathData pathListArray[STRATEGY_2018_NAVIGATION_PATH_LIST_TEST_ARRAY_LENGTH];

static BitList outgoingPathBitList;
static unsigned int outgoingPathBitArray[STRATEGY_2018_BIT_LIST_NAVIGATION_TEST_ARRAY_LENGTH];
static BitList availablePathBitList;
static unsigned int availablePathBitArray[STRATEGY_2018_BIT_LIST_NAVIGATION_TEST_ARRAY_LENGTH];


// ------------------------------------------------------ LOCATIONS --------------------------------------------------------------------
// -> General Points
static Location* startAreaLocation;
static Location* distributor1FrontLocation;
static Location* distributor2FrontLocation;
static Location* beeLocation;
static Location* switchLocation;
static Location* garbageReleaseLocation;

static Location* buildingAreaLocation;
static Location* buildingLeft1Location;
static Location* buildingLeft2Location;
static Location* buildingMiddle1Location;
static Location* buildingMiddle2Location;
static Location* buildingRight1Location;
static Location* buildingRight2Location;

// ------------------------------------------------------- PATHS -------------------------------------------------------------------------

PathData* startAreaToDistributor1FrontPath;
PathData* greenDistributor1ToBeePath;
PathData* beeToGreenDistributor2Path;
PathData* beeToGreenBuildingAreaPath;
PathData* greenBuildingAreaToSwitch1Path;
PathData* switch1ToGreenDistributor2Path;
PathData* greenDistributor2ToGarbageAreaFrontPath;
PathData* garbageAreaFrontPathTo;

// ------------------------------------------------------- TARGETS -----------------------------------------------------------------------

// Targets List
static GameTarget distributor1GameTarget;

// ------------------------------------------------------- TARGETS ACTIONS ---------------------------------------------------------------

static GameTargetAction distributor1TakeTargetAction;

// ------------------------------------------------------- TARGETS ACTIONS ITEMS --------------------------------------------------------

static GameTargetActionItemList distributor1TakeTargetActionItemList;

// ------------------------------------------------------- STRATEGIES ----------------------------------------------------------------

// strategies
static GameStrategy strategy1;

// strategies Items
static GameStrategyItem distributor1StrategyItem;

// ------------------------------------------------------- INITIALIZATION ------------------------------------------------------------

void setColor(enum TeamColor color) {
	GameStrategyContext* context = getStrategyContext();

	appendStringAndDec(getInfoOutputStreamLogger(), "setColor:", color);
	println(getInfoOutputStreamLogger());

	context->color = color;
	// changeLocationsForColor();
	int angle = 675;
	if (!isGreen()) {
		angle = -angle;
		context->robotPosition.y = 2840;
	}
	else {
		context->robotPosition.y = 160;
	}
	context->robotPosition.x = 160;

	context->robotAngle = angle;

	printStrategyAllDatas(getInfoOutputStreamLogger());
}

void initLocations2018(void) {
    startAreaLocation = addNavigationLocation(START_AREA, START_AREA_X, START_AREA_Y);
    distributor1FrontLocation = addNavigationLocation(DISTRIBUTOR_1, DISTRIBUTOR_1_X, DISTRIBUTOR_1_Y);
    distributor2FrontLocation = addNavigationLocation(DISTRIBUTOR_2, DISTRIBUTOR_2_X, DISTRIBUTOR_2_Y);

    beeLocation = addNavigationLocation(BEE, BEE_X, BEE_Y);
    switchLocation = addNavigationLocation(SWITCH, SWITCH_X, SWITCH_Y);
    garbageReleaseLocation = addNavigationLocation(GARBAGE, GARBAGE_RELEASE_POINT_X, GARBAGE_RELEASE_POINT_Y);

    buildingAreaLocation = addNavigationLocation(BUILDING_AREA, BUILDING_AREA_X, BUILDING_AREA_Y);
    buildingLeft1Location = addNavigationLocation(BUILDING_LEFT_1, BUILDING_LEFT_1_X, BUILDING_LEFT_1_Y);
    buildingLeft2Location = addNavigationLocation(BUILDING_LEFT_2, BUILDING_LEFT_2_X, BUILDING_LEFT_2_Y);

    buildingMiddle1Location = addNavigationLocation(BUILDING_MIDDLE_1, BUILDING_MIDDLE_1_X, BUILDING_MIDDLE_1_Y);
    buildingMiddle2Location = addNavigationLocation(BUILDING_MIDDLE_2, BUILDING_MIDDLE_2_X, BUILDING_MIDDLE_2_Y);

    buildingRight1Location = addNavigationLocation(BUILDING_RIGHT_1, BUILDING_RIGHT_1_X, BUILDING_RIGHT_1_Y);
    buildingRight2Location = addNavigationLocation(BUILDING_RIGHT_2, BUILDING_RIGHT_2_X, BUILDING_RIGHT_2_Y);
}

void initPaths2018(int index) {
    startAreaToDistributor1FrontPath = addNavigationPath(startAreaLocation, distributor1FrontLocation, STARTAREA_TO_DISTRIBUTOR_1_COST, 0x10, 0x10, ANGLE_45, -ANGLE_60, STARTAREA_TO_DISTRIBUTOR_1_ACCELERATION_FACTOR, STARTAREA_TO_DISTRIBUTOR_1_SPEED_FACTOR);
    greenDistributor1ToBeePath = addNavigationPath(distributor1FrontLocation, beeLocation, DISTRIBUTOR_1_TO_BEE_COST, 0x80, 0x10, -ANGLE_60, 0, DISTRIBUTOR_1_TO_BEE__ACCELERATION_FACTOR, DISTRIBUTOR_1_TO_BEE_SPEED_FACTOR);
    beeToGreenDistributor2Path = addNavigationPath(beeLocation, distributor2FrontLocation, BEE_TO_DISTRIBUTOR_2_COST, 0x37, 0x96, 0, ANGLE_30, BEE_TO_DISTRIBUTOR_2__ACCELERATION_FACTOR, BEE_TO_DISTRIBUTOR_2_SPEED_FACTOR);
    beeToGreenBuildingAreaPath = addNavigationPath(beeLocation, buildingAreaLocation, BEE_TO_BUILDING_AREA_COST, 0x10, 0x60, 0, ANGLE_30, BEE_TO_BUILDING_AREA_ACCELERATION_FACTOR, BEE_TO_BUILDING_AREA_SPEED_FACTOR);
    greenBuildingAreaToSwitch1Path = addNavigationPath(buildingAreaLocation, switchLocation, BUILDING_AREA_TO_SWITCH_COST, 0x10, 0x20, ANGLE_30, 0, BUILDING_AREA_TO_SWITCH_ACCELERATION_FACTOR, BUILDING_AREA_TO_SWITCH_SPEED_FACTOR);

    // switch1ToGreenDistributor2Path = addNavigationPath(switchLocation, distributor2FrontLocation, SWITCH_TO_DISTRIBUTOR_2_ACCELERATION_FACTOR, 0x20, 0x80, 0, ANGLE_30);
    /*
    PathData* greenDistributor2ToGarbageAreaFrontPath;
    PathData* garbageAreaFrontPathTo;
    */
}

void initTargets2018(void) {
	clearGameTargets();
}

void initTargetActions2018(void) {
}

void initTargetActionsItems2018() {
}

/**
* @private.
*/
void initStrategies2018() {
	clearGameStrategies();
	addGameStrategy(&strategy1, "S1");
}

void initStrategiesItems2018(int strategyIndex) {
//	addGameStrategyItem(&strategy1, &distributor1StrategyItem, );
}

void initStrategy2018(int strategyIndex) {

	initLocationList(&locationList, (Location(*)[]) &locationListArray, STRATEGY_2018_BIT_LIST_NAVIGATION_TEST_ARRAY_LENGTH);
	initPathList(&pathList, (PathData(*)[]) &pathListArray, STRATEGY_2018_NAVIGATION_PATH_LIST_TEST_ARRAY_LENGTH);
	initBitList(&outgoingPathBitList, (unsigned int(*)[]) &outgoingPathBitArray, STRATEGY_2018_BIT_LIST_NAVIGATION_TEST_ARRAY_LENGTH);
	initBitList(&availablePathBitList, (unsigned int(*)[]) &availablePathBitArray, STRATEGY_2018_BIT_LIST_NAVIGATION_TEST_ARRAY_LENGTH);

	initNavigation(&locationList, &pathList, &outgoingPathBitList, &availablePathBitList);

	initLocations2018();
	initPaths2018(strategyIndex);

	initTargets2018();
	initTargetActions2018();
	initTargetActionsItems2018();

	initStrategies2018();
	initStrategiesItems2018(strategyIndex);

	GameStrategy* strategy = getGameStrategy(0);
	GameStrategyContext* strategyContext = getStrategyContext();
	strategyContext->gameStrategy = strategy;
	strategyContext->maxTargetToHandle = getGameTargetList()->size;

	//OutputStream* debugOutputStream = getInfoOutputStreamLogger();
	//printStrategyAllDatas(debugOutputStream);

	// opponent
	Point* p = &(getStrategyContext()->opponentRobotPosition);
	p->x = 0;
	p->y = 0;

	// obstacle
	p = &(getStrategyContext()->lastObstaclePosition);
	p->x = 0;
	p->y = 0;

	strategyContext->hasMoreNextSteps = true;

	// reinitialize the game board to change elements / targets ...
}

void printStrategyAllDatas(OutputStream* outputStream) {
	printLocationListTable(outputStream, getNavigationLocationList());
	printPathListTable(outputStream, getNavigationPathList());
	printGameTargetList(outputStream);
	printGameStrategyTableList(outputStream);
	printGameStrategyContext(outputStream, getStrategyContext());
}
