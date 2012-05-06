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
		appendString(getOutputStreamLogger(DEBUG), "\tcomputeBestNextTargetAction:\n");	
	#endif

	// Find best Target, store LocationList in the context in currentTrajectory
	computeBestNextTarget(&strategyContext);

	#ifdef DEBUG_STRATEGY_HANDLER
		appendString(getOutputStreamLogger(DEBUG), "\t\tbestTarget:");
		if (strategyContext.currentTarget != NULL) {
			printGameTarget(getOutputStreamLogger(DEBUG), strategyContext.currentTarget, FALSE);
		}
		else {
			appendString(getOutputStreamLogger(DEBUG), "NULL\n");
		}
		appendString(getOutputStreamLogger(DEBUG), "\t\tbestTargetAction:");
		if (strategyContext.currentTargetAction != NULL) {
			printGameTargetAction(getOutputStreamLogger(DEBUG), strategyContext.currentTargetAction, FALSE);
		}
		else {
			appendString(getOutputStreamLogger(DEBUG), "NULL\n");
		}
	#endif
}

void markTargetAsHandled() {
	// mark the target as unavailable
	strategyContext.currentTarget->available = FALSE;
	// reset current Target
	strategyContext.currentTarget = NULL;
	strategyContext.currentTargetAction = NULL;
}

/**
 * @private
 */
void executeTargetActions() {
	#ifdef DEBUG_STRATEGY_HANDLER
		appendString(getOutputStreamLogger(DEBUG), "executeTargetActions\n");
	#endif

	GameTargetAction* targetAction = strategyContext.currentTargetAction;
	GameTargetActionItemList* actionItemList = targetAction->actionItemList;
	if (actionItemList == NULL) {
		#ifdef DEBUG_STRATEGY_HANDLER
			appendString(getOutputStreamLogger(DEBUG), "-> no actions for this target\n");
		#endif
		markTargetAsHandled();
		nextStep();
		return;
	}

	// There is actionItem in progress
	if (actionItemList != NULL && targetActionItemListHasNext(actionItemList)) {
		GameTargetActionItem* actionItem = targetActionItemListNext(actionItemList);

		#ifdef DEBUG_STRATEGY_HANDLER
			printGameTargetActionItem(getOutputStreamLogger(DEBUG), actionItem);
		#endif

		// Do the action item
		actionItem->actionItem();
	}
	else {
		markTargetAsHandled();
		nextStep();
	}
}


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
		// printLocationList(getOutputStreamLogger(DEBUG), "currentTrajectory:", currentTrajectory);	
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

	if (getLocationCount(&(strategyContext.currentTrajectory)) != 0) {
		handleCurrentTrajectory();
	}
	else if (targetAction != NULL) {
		executeTargetActions();
	}
	else if (targetAction == NULL) {
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


