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

// ------------------------------------------------------- PATHS -------------------------------------------------------------------------

PathData* startAreaToDistributor1FrontPath;

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
}

void initPaths2012(int index) {
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
	// initPaths2018(strategyIndex);

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
