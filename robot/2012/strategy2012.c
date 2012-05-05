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
static Location startAreaLocation; 
static Location bullion1Location;
static Location bottle1Location;
static Location bottle2Location;
static Location cdTakeLocation;
static Location dropZone1Location;
static Location bullionMiddleLocation;
static Location rightBullionLocation;

// Paths
static Path startAreaToBullion1;
static Path bullion1ToBottle1;
static Path bottle1ToBottle2;
static Path bottle2ToCD;
static Path cdToDropZone1;
static Path dropZone1ToBullionMiddle1;
static Path bullionMiddle1ToRightBullion1;
static Path rightBullion1ToDropZone1;
static Path bullionMiddle1ToLeftBullion1;
static Path leftBullion1ToStartAreaFrontOf;
static Path startAreaFrontOfTostartAreaDropZone1;


// Target actionList
static GameTargetAction bullion1TargetAction;

// strategies
static GameStrategy strategy1;

// strategies Items
static GameStrategyItem takeBullionFirst;



void initLocations2012() {
	addNavigationLocation(&startAreaLocation, START_AREA, START_AREA_X, START_AREA_Y);
	addNavigationLocation(&bullion1Location, BULLION_1, BULLION_1_X, BULLION_1_Y);
	addNavigationLocation(&bottle1Location, BOTTLE_1, BOTTLE_1_X, BOTTLE_1_Y);
	addNavigationLocation(&bottle2Location, BOTTLE_2, BOTTLE_2_X, BOTTLE_2_Y);
	addNavigationLocation(&cdTakeLocation, CD_TAKE, CD_TAKE_X, CD_TAKE_Y);
}

void initPaths2012() {
	addNavigationPath(&startAreaToBullion1, &startAreaLocation, &bullion1Location, START_AREA_TO_BULLION_1_COST,  0x40, 0x40, 0x02A3, ANGLE_NEG_90, START_AREA_TO_BULLION_1_SPEED_FACTOR); 
	addNavigationPath(&bullion1ToBottle1, &bullion1Location, &bottle1Location, BULLION_1_TO_BOTTLE_1_COST, 0xEC, 0xC0, ANGLE_NEG_90, ANGLE_180, BULLION_1_TO_BOTTLE_1_SPEED_FACTOR);
	addNavigationPath(&bottle1ToBottle2, &bottle1Location, &bottle2Location, BOTTLE_1_TO_BOTTLE_2_COST, 0x57, 0x0A, ANGLE_180, 0, BOTTLE_1_TO_BOTTLE_2_SPEED_FACTOR);
	addNavigationPath(&bottle2ToCD, &bottle2Location, &cdTakeLocation, BOTTLE_2_TO_CD_COST, 0x1B, 0x30, 0, 0xFAF6, BOTTLE_2_TO_CD_SPEED_FACTOR);
	addNavigationPath(&cdToDropZone1, &cdTakeLocation, &dropZone1Location, CD_TO_DROP_ZONE_1_COST, 0x11, 0x26, 0xFAF6, ANGLE_NEG_90, CD_TO_DROP_ZONE_1_SPEED_FACTOR);

}

void initTargets2012() {
	addGameTarget(&bullion1Target, BULLION_1, BULLION_GAIN, &bullion1Location);
	addGameTarget(&bottle1Target, BOTTLE_1, BOTTLE_GAIN, &bottle1Location);
	addGameTarget(&bottle2Target, BOTTLE_2, BOTTLE_GAIN, &bottle2Location);
	addGameTarget(&cd4Target, CD_TAKE, CD_4_GAIN, &cdTakeLocation);
	/*
	addGameTarget(&bullionRight1Target, BULLION_RIGHT_1, BULLION_GAIN);
	addGameTarget(&bullionRight2Target, BULLION_RIGHT_2, BULLION_GAIN);
	addGameTarget(&bullionLeft1Target, BULLION_LEFT_1, BULLION_GAIN);
	addGameTarget(&bullionLeft2Target, BULLION_LEFT_2, BULLION_GAIN);
	*/
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
	initLocations2012();
	initPaths2012();

	initTargets2012();
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
