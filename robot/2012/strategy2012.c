#include <stdlib.h>

#include "strategy2012.h"

#include "../../navigation/locationList.h"
#include "../../navigation/path.h"
#include "../../navigation/pathList.h"
#include "../../navigation/navigation.h"


#include "../../robot/strategy/gameStrategy.h"
#include "../../robot/strategy/gameStrategyList.h"

#include "../../robot/strategy/gameTarget.h"
#include "../../robot/strategy/gameTargetList.h"

// Targets List
static GameTarget bullion1Target;
static GameTarget bottle1Target;
static GameTarget bottle2Target;
static GameTarget cd4Target;
static GameTarget bullionRight1Target;
static GameTarget bullionRight2Target;
static GameTarget bullionLeft1Target;
static GameTarget bullionLeft2Target;

// Locations
static LocationList gameLocationList;
static Location startAreaLocation; 
static Location bullion1Location;
static Location bottle1Location;
static Location bottle2Location;

// Paths
static Path startAreaToBullion1;
static Path Bullion1ToBottle1;
static Path Bottle1ToBottle2;
static Path Bottle2ToCD;
static Path CDToDropZone1;
static Path DropZone1ToBullionMiddle1;
static Path BullionMiddle1ToRightBullion1;
static Path RightBullion1ToDropZone1;
static Path BullionMiddle1ToLeftBullion1;
static Path LeftBullion1ToStartAreaFrontOf;
static Path StartAreaFrontOfTostartAreaDropZone1;


// Target actionList
static GameTargetAction bullion1TargetAction;

// strategies
static GameStrategy strategy1;

// strategies Items
static GameStrategyItem takeBullionFirst;

void initTargets2012() {
	addGameTarget(&bullion1Target, BULLION_1);
	addGameTarget(&bottle1Target, BOTTLE_1);
	addGameTarget(&bottle2Target, BOTTLE_2);
	addGameTarget(&cd4Target, CD_4);
	addGameTarget(&bullionRight1Target, BULLION_RIGHT_1);
	addGameTarget(&bullionRight2Target, BULLION_RIGHT_2);
	addGameTarget(&bullionLeft1Target, BULLION_LEFT_1);
	addGameTarget(&bullionLeft2Target, BULLION_LEFT_2);
}

void initLocations2012() {
	addLocation(&gameLocationList, &startAreaLocation, START_AREA, START_AREA_X, START_AREA_Y);
	addLocation(&gameLocationList, &bullion1Location, BULLION_1, BULLION_1_X, BULLION_1_Y);
	addLocation(&gameLocationList, &bottle1Location, BOTTLE_1, BOTTLE_1_X, BOTTLE_1_Y);
	addLocation(&gameLocationList, &bottle2Location, BOTTLE_2, BOTTLE_2_X, BOTTLE_2_Y);
	addLocation(&gameLocationList, &bottle2Location, BOTTLE_2, BOTTLE_2_X, BOTTLE_2_Y);
}

void initPaths2012() {
	addNavigationPath(&startAreaToBullion1, &startAreaLocation, &bullion1Location, START_AREA_TO_BULLION_1_COST,  0x40, 0x40, 0x02A3, ANGLE_NEG_90, START_AREA_TO_BULLION_1_SPEED_FACTOR); 

}

void initTargetActions2012() {
	addTargetAction(&(bullion1Target.actionList), &bullion1TargetAction, &startAreaLocation, &bullion1Location, 2);
}

void initStrategies2012() {
	addGameStrategy(&strategy1, "S1");
}

void initStrategiesItems2012() {
	addGameStrategyItem(&strategy1, &takeBullionFirst);
}

void initStrategy2012() {
	initTargets2012();
	initLocations2012();
	initTargetActions2012();
	initStrategies2012();
}



/**
 * Get the way to have bullion1.
 */
GameTarget* getBullion1Target() {
	/*
	if (bullion1Target == NULL) {
			
	}
	*/
	// addTarget(bullion1Target->actionList, bullion1TargetAction, startArea, bullion1Location, 2);
	return &bullion1Target;
}

/*
private ITargetAction[] addSymmetricTargetAction(ITarget[] targets, String start, String end, int time) {
	// red
	ITargetAction a1 = addTargetAction(targets[0], NavigationMap2012.getRedName(start), NavigationMap2012.getRedName(end),
			time);
	// violet
	ITargetAction a2 = addTargetAction(targets[1], NavigationMap2012.getVioletName(start),
			NavigationMap2012.getVioletName(end), time);
	return new ITargetAction[] { a1, a2 };
}
*/
