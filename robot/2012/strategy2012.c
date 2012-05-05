#include <stdlib.h>

#include "strategy2012.h"

#include "../../navigation/locationList.h"


#include "../../robot/strategy/gameTarget.h"
#include "../../robot/strategy/gameTargetList.h"

#define COLOR_COUNT		 2

// Targets List
static GameTarget bullion1Target;
static GameTarget bottle1Target;
static GameTarget bottle2Target;
static GameTarget cd4Target;
static GameTarget bullionRight1Target;
static GameTarget bullionRight2Target;
static GameTarget bullionLeft1Target;
static GameTarget bullionLeft2Target;


// start Area
static Location startArea; 
static Location bullion1Location;
static Location bottle1Location;
static Location bottle2Location;


static LocationList gameLocationList;

// static GameTargetAction[COLOR_COUNT] bullion1TargetAction

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
	addLocation(&gameLocationList, &startArea, START_AREA, START_AREA_X, START_AREA_Y);
	addLocation(&gameLocationList, &startArea, BULLION_1, BULLION_1_X, BULLION_1_Y);
	addLocation(&gameLocationList, &startArea, BOTTLE_1, BOTTLE_1_X, BOTTLE_1_Y);
	addLocation(&gameLocationList, &startArea, BOTTLE_2, BOTTLE_2_X, BOTTLE_2_Y);

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
