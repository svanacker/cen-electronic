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
	// global points
	LocationList* navigationLocationList = getNavigationLocationList();

	Point* robotPosition = &(strategyContext.robotPosition);
	// Find nearest location
	strategyContext.nearestLocation = getNearestLocation(navigationLocationList, robotPosition->x, robotPosition->y);
	
	// Find best Target, store LocationList in the context in currentTrajectory
	strategyContext.currentTargetAction = getBestNextTarget(&strategyContext);
}

/**
 * @private
 */
void executeTargetActions() {
	/*
	if (currentActions == null) {
		ITargetActionItemList actions = currentTargetAction.getItems();
		currentActions = actions.iterator();
	}
	if (currentActions != null && currentActions.hasNext()) {
		ITargetActionItem action = currentActions.next();
		RobotDeviceRequest request = action.getRequest();
		sendRequest(request);
		displayRequest(request);
		if (!(request instanceof NavigationRequest) && !(request instanceof SleepRequest)) {
			nextStep();
		}
	} else {
		// the target is no more available
		appendString(getOutputStreamLogger(DEBUG), "no more actions");
		currentTargetAction.getTarget().setAvailable(false);
		currentActions = null;
		currentTargetAction = null;
		currentTrajectory = null;
		displayRequest(null);
		nextStep();
	}
	*/
}

void nextStep(GameStrategyContext* strategyContext) {
	GameTargetAction* targetAction = strategyContext->currentTargetAction;

	if (targetAction == NULL) {
		appendString(getOutputStreamLogger(DEBUG), "findNextTarget\n");
		// no target, search a new one
		findNextTarget();
		// TODO
		/*
		if (getLocationCount(strategyContext->currentTrajectory) != 0) {
			
		}
		*/
	}
	/*
	if (currentActions != null) {
			LOGGER.fine("executeTargetActions 1");
			// actions pending
			executeTargetActions();
		} else if (currentTrajectory != null) {
			LOGGER.fine("handleCurrentTrajectory");
			// trajectory if any
			handleCurrentTrajectory();
		} else if (currentTargetAction == null) {
			LOGGER.fine("findNextTarget");
			// no target, search a new one
			findNextTarget();
			if (currentTrajectory != null) {
				// next location
				nextStep();
			}
		} else {
			LOGGER.fine("executeTargetActions 2");
			// executes the actions of the active target
			executeTargetActions();
		}
	*/
}

void motionFollowPath(Path* path) {
	Location* location = path->location2;
	motionDriverBSplineAbsolute(location->x, location->y,
								path->angle2, 
								path->controlPointDistance1, path->controlPointDistance2);
}

void handleCurrentTrajectory() {
	LocationList* currentTrajectory = &(strategyContext.currentTrajectory);
	if (currentTrajectory->count < 2) {
		// no more locations to reach
		clearLocationList(currentTrajectory);
		// nextStep();
		return;
	}

	Location* start = getLocation(currentTrajectory, 0);
	Location* end = getLocation(currentTrajectory, 1);
	Path* path = getPathOfLocations(getNavigationPathList(), start, end);
	motionFollowPath(path);
	/*
	RobotDeviceRequest request = getRequest(start, path);
	sendRequest(request);
	if (!(request instanceof RotationRequest)) {
		currentTrajectory.remove(0);
	}
	*/
}
