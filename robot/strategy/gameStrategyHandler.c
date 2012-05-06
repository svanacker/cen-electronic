#include "gameStrategyHandler.h"

#include "gameStrategyContext.h"

#include "../../navigation/location.h"
#include "../../navigation/locationList.h"
#include "../../navigation/navigation.h"
#include "../../navigation/path.h"
#include "../../navigation/pathList.h"

#include "../../drivers/motion/motionDriver.h"

void nextStep(GameStrategyContext* strategyContext) {
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

void handleCurrentTrajectory(GameStrategyContext* strategyContext) {
	LocationList* currentTrajectory = &(strategyContext->currentTrajectory);
	if (currentTrajectory->count < 2) {
		// no more locations to reach
		// currentTrajectory = null;
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
