#include <math.h>
#include <stdlib.h>

#include "gameStrategyHandler.h"
#include "gameStrategyMotionHandler.h"
#include "gameTargetActionList.h"
#include "gameTargetAction.h"
#include "gameStrategyContext.h"

#include "nextGameStrategyItemComputer.h"

#include "../../common/error/error.h"

#include "../../common/math/cenMath.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerList.h"

#include "../../client/motion/simple/clientMotion.h"

#include "../../motion/extended/bspline.h"
#include "../../motion/extended/bsplineList.h"

#include "../../navigation/location.h"
#include "../../navigation/locationList.h"
#include "../../navigation/locationListComputer.h"
#include "../../navigation/navigation.h"
#include "../../navigation/navigationComputer.h"
#include "../../navigation/path.h"
#include "../../navigation/pathList.h"

#include "../../client/motion/extended/clientExtendedMotion.h"
#include "../../client/motion/simple/clientMotion.h"
#include "../../client/motion/position/clientTrajectory.h"

#include "../../robot/strategy/gameTargetList.h"
#include "../../robot/2018/strategy2018Utils.h"
#include "../../robot/robot.h"

void initStrategyHandler(GameStrategyContext* gameStrategyContext) {
}


void updateNearestLocation(GameStrategyContext* gameStrategyContext) {
    gameStrategyContext->nearestLocation = getNearestLocationFromGameStrategyContext (gameStrategyContext);
}

GameTarget* findNextTarget(GameStrategyContext* gameStrategyContext) {
    updateNearestLocation(gameStrategyContext);
    
    // We wait the notification
    if (gameStrategyContext->trajectoryType != TRAJECTORY_TYPE_NONE) {
        return NULL;
    }

    // Find best Target, store LocationList in the context in currentTrajectory
    GameTarget* result = computeBestNextTarget(gameStrategyContext);
    gameStrategyContext->currentTarget = result;

    return result;
}

bool executeTargetActionItemList(GameStrategyContext* gameStrategyContext, GameTargetActionItemList* actionItemList) {
    bool result = true;
    unsigned int actionItemIndex;
    // Loop on all action Items to do
    for (actionItemIndex = 0; actionItemIndex < actionItemList->size; actionItemIndex++) {
        GameTargetActionItem* actionItem = getGameTargetActionItem(actionItemList, actionItemIndex);
        // Do only action not done and enabled
        if (actionItem->status != ACTION_ITEM_STATUS_TODO || !(actionItem->enabled)) {
            continue;
        }

        // Do the action item, and track if there will be an error
        if (!doGameTargetActionItem(actionItem, (int*)gameStrategyContext)) {
            result = false;
        }
    }
    return result;
}

/**
* Handle the different types of actions : moving / preparing, handling / dropping
* @private
*/
bool handleActions(GameStrategyContext* gameStrategyContext) {
    GameTarget* currentTarget = gameStrategyContext->currentTarget;
    if (currentTarget == NULL) {
        return false;
    }
    GameTargetActionList* actionList = &(currentTarget->actionList);
    GameTargetAction* targetAction = getNextGameTargetActionTodo(actionList, gameStrategyContext->nearestLocation);

    if (targetAction == NULL) {
        return false;
    }
    enum ActionType actionType = targetAction->type;

    // If the action is to move from startLocation to endLocation
    // Move action has no gameTargetActionItemList
    if (actionType == ACTION_TYPE_MOVE) {
        Navigation* navigation = gameStrategyContext->navigation;
        PathList* pathList = getNavigationPathList(navigation);
        Location* startLocation = targetAction->startLocation;
        Location* endLocation = targetAction->endLocation;
        PathData* pathData = getPathOfLocations(pathList, startLocation, endLocation);
        if (pathData == NULL) {
            writeError(PATH_LIST_NULL);
            return false;
        }
        else {
            motionFollowPath(gameStrategyContext, pathData);
            // TODO : Must be done AFTER that the move has been done
            targetAction->status = ACTION_STATUS_DONE;
        }
    }
    else {
        GameTargetActionItemList* actionItemList = targetAction->actionItemList;
        if (executeTargetActionItemList(gameStrategyContext, actionItemList)) {
            // All Items of the actions were done successfully
            targetAction->status = ACTION_STATUS_DONE;
        }
        else {
            // We mark the action in error
            targetAction->status = ACTION_STATUS_ERROR;
        }
    }

    // Update the status of the target from the status of each actions
    updateTargetStatus(currentTarget);
    if (currentTarget->status == TARGET_HANDLED) {
        currentTarget->gain = currentTarget->potentialGain;
        gameStrategyContext->endMatch->scoreToShow += (int) currentTarget->gain;
    }

    return true;
}

/**
* Handle the trajectory and return true if we go to a location, false else.
* @private
*/
bool handleTrajectoryToActionStart(GameStrategyContext* gameStrategyContext) {
    GameTarget* currentTarget = gameStrategyContext->currentTarget;
    if (currentTarget == NULL) {
        return false;
    }
    // Only manage Target which are available
    if (currentTarget->status != TARGET_AVAILABLE) {
        return false;
    }
    Navigation* navigation = gameStrategyContext->navigation;
    Location* startLocation = gameStrategyContext->nearestLocation;

    // Start Location could be null if the nearest Location was not found (because too far)
    if (startLocation == NULL) {
        // Go back to the previous point
        return false;
    }

    // If the point of the robot is the same than the startLocation of the target Actions, we do not do anything
    if (startLocation == currentTarget->startLocation) {
        // We consider now that 
        currentTarget->status = TARGET_STARTING_POINT_REACHED;
        return false;
    }
    // Take the next location to follow
    Location* endLocation = startLocation->computedNextLocation;
    if (endLocation == NULL) {
        currentTarget->status = TARGET_MISSED;
        clearCurrentTarget(gameStrategyContext);
        return false;
    }

    PathList* pathList = getNavigationPathList(navigation);
    PathData* pathData = getPathOfLocations(pathList, startLocation, endLocation);

    // We wait that we end the move
    if (gameStrategyContext->trajectoryType != TRAJECTORY_TYPE_NONE) {
        return false;
    }
    // Check if to follow the path, we need to do first a rotation (to avoid problem on bSpline)
    if (!motionRotateToFollowPath(gameStrategyContext, pathData)) {
        // If this is not the case, we ask to follow the path
        motionFollowPath(gameStrategyContext, pathData);
    }
    return true;
}

bool nextStep(GameStrategyContext* gameStrategyContext) {
    // The start point is the nearest point of the robot
    // TODO : Restrict the nearest Point to the list of the trajectory to reach the target and not all locations ?
    updateNearestLocation(gameStrategyContext);

    // Launch command to follow the different actions (and move if action->endLocation != action->startLocation)
    if (handleActions(gameStrategyContext)) {
        // We do not do anything, we wait that the robot reach his target
        return true;
    }

    // Launch command to follow the trajectory until the action location start
    if (handleTrajectoryToActionStart(gameStrategyContext)) {
        // We do not do anything, we wait that the robot reach his target
        return true;
    }

    return false;
}

/**
 * Function which must be called by the main function to.
 */
bool nextTargetOrNextStep(GameStrategyContext* gameStrategyContext) {
    enum TrajectoryType trajectoryType = gameStrategyContext->trajectoryType;
    if (trajectoryType != TRAJECTORY_TYPE_NONE) {
        return false;
    }
    // Always find a new target if no target is available
    GameTarget* currentTarget = gameStrategyContext->currentTarget;
    if (currentTarget == NULL || currentTarget->status == TARGET_HANDLED) {
        clearCurrentTarget(gameStrategyContext);
        findNextTarget(gameStrategyContext);
    }

    return nextStep(gameStrategyContext);
}