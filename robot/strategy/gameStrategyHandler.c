#include <stdlib.h>

#include "gameStrategyHandler.h"

#include "gameStrategyContext.h"

#include "nextGameStrategyItemComputer.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../navigation/location.h"
#include "../../navigation/locationList.h"
#include "../../navigation/navigation.h"
#include "../../navigation/path.h"
#include "../../navigation/pathList.h"

#include "../../drivers/motion/motionDriver.h"

// Strategy Context
static GameStrategyContext strategyContext;

GameStrategyContext* getStrategyContext() {
	return &strategyContext;
}

/**
 * @private
 */
void findNextTarget() {
	appendString(getOutputStreamLogger(DEBUG), "findNextTarget\n");

	// global points
	LocationList* navigationLocationList = getNavigationLocationList();

	Point* robotPosition = &(strategyContext.robotPosition);
	// Find nearest location
	strategyContext.nearestLocation = getNearestLocation(navigationLocationList, robotPosition->x, robotPosition->y);

	#ifdef DEBUG_STRATEGY_HANDLER
		appendString(getOutputStreamLogger(DEBUG), "\tNearest Location:");	
		printLocation(getOutputStreamLogger(DEBUG), strategyContext.nearestLocation);
		appendString(getOutputStreamLogger(DEBUG), "\tgetBestNextTarget:");	
	#endif

	// Find best Target, store LocationList in the context in currentTrajectory
	strategyContext.currentTargetAction = getBestNextTarget(&strategyContext);

	#ifdef DEBUG_STRATEGY_HANDLER
		printGameTargetAction(getOutputStreamLogger(DEBUG), strategyContext.currentTargetAction);
	#endif
}

/**
 * @private
 */
void executeTargetActions() {
	appendString(getOutputStreamLogger(DEBUG), "executeTargetActions\n");

	GameTargetAction* targetAction = strategyContext.currentTargetAction;
	GameTargetActionItemList* actionItemList = targetAction->actionItemList;
	if (actionItemList == NULL) {
		#ifdef DEBUG_STRATEGY_HANDLER
			appendString(getOutputStreamLogger(DEBUG), "-> no actions for this target\n");
		#endif
		return;
	}

	if (actionItemList != NULL) {
		// strategyContext.actionItemList = actionItemList;
	}
	if (actionItemList != NULL && targetActionItemListHasNext(actionItemList)) {
		GameTargetActionItem* actionItem = targetActionItemListNext(actionItemList);

		#ifdef DEBUG_STRATEGY_HANDLER
			appendStringAndDec(getOutputStreamLogger(DEBUG), "-> nextActionItem:", (int) actionItem);
			println(getOutputStreamLogger(DEBUG));
		#endif

		// Do the action item
		actionItem->actionItem();
	}
	else {
		// strategyContext->actionItem = NULL;
		strategyContext.currentTargetAction = NULL;
		strategyContext.currentTarget->available = FALSE;
		clearLocationList(&(strategyContext.currentTrajectory));
		nextStep();
	}
}


/**
 * @private
 */
void motionFollowPath(Path* path) {
	Location* location = path->location2;

	#ifdef DEBUG_STRATEGY_HANDLER
		appendString(getOutputStreamLogger(DEBUG), "motionFollowPath:goto:");	
		printLocation(getOutputStreamLogger(DEBUG), location);
	#endif

	motionDriverBSplineAbsolute(location->x, location->y,
								path->angle2, 
								path->controlPointDistance1, path->controlPointDistance2);

	// Simulate as if the robot goes to the position with a small error
	#ifdef SIMULATE_ROBOT
		strategyContext.robotPosition.x = location->x + 1;
		strategyContext.robotPosition.y = location->y + 1;
	#endif
}

/**
* @private
*/
void handleCurrentTrajectory() {
	#ifdef DEBUG_STRATEGY_HANDLER
		appendString(getOutputStreamLogger(DEBUG), "handleCurrentTrajectory\n");	
	#endif

	LocationList* currentTrajectory = &(strategyContext.currentTrajectory);

	#ifdef DEBUG_STRATEGY_HANDLER
		printLocationList(getOutputStreamLogger(DEBUG), "currentTrajectory:", currentTrajectory);	
	#endif

	if (currentTrajectory->count < 2) {

		#ifdef DEBUG_STRATEGY_HANDLER
			appendString(getOutputStreamLogger(DEBUG), "no more locations to reach\n");	
		#endif

		// no more locations to reach
		clearLocationList(currentTrajectory);
		// nextStep();
		return;
	}

	Location* start = getLocation(currentTrajectory, 0);
	Location* end = getLocation(currentTrajectory, 1);
	Path* path = getPathOfLocations(getNavigationPathList(), start, end);
	motionFollowPath(path);
	removeFirstLocation(currentTrajectory);
}


void nextStep() {
	#ifdef DEBUG_STRATEGY_HANDLER
		appendString(getOutputStreamLogger(DEBUG), "nextStep\n");	
	#endif

	GameTargetAction* targetAction = strategyContext.currentTargetAction;

	if (targetAction != NULL) {
		executeTargetActions();
	}
	else if (getLocationCount(&(strategyContext.currentTrajectory)) != 0) {
		handleCurrentTrajectory();
	}
	if (targetAction == NULL) {
		// no target, search a new one
		findNextTarget();
		// Next target created a new current trajectory
		if (getLocationCount(&(strategyContext.currentTrajectory)) != 0) {
			handleCurrentTrajectory();			
		}
	} else {
		executeTargetActions();
	}
}


