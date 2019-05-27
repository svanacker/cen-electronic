#include <math.h>
#include <stdlib.h>

#include "../../common/error/error.h"

#include "../../common/math/cenMath.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../navigation/location.h"
#include "../../navigation/locationList.h"
#include "../../navigation/locationListComputer.h"
#include "../../navigation/navigation.h"
#include "../../navigation/navigationComputer.h"
#include "../../navigation/path.h"
#include "../../navigation/pathList.h"

#include "../../robot/strategy/gameTargetList.h"
#include "../../robot/strategy/gameStrategyHandler.h"
#include "../../robot/strategy/gameStrategyMotionHandler.h"
#include "../../robot/strategy/gameStrategyPositionHandler.h"
#include "../../robot/strategy/gameTargetActionList.h"
#include "../../robot/strategy/gameTargetAction.h"
#include "../../robot/strategy/gameStrategyContext.h"
#include "../../robot/strategy/nextGameStrategyItemComputer.h"

#include "../../robot/robot.h"

void initStrategyHandler(GameStrategyContext* gameStrategyContext) {
}


void updateGameStrategyContextNearestLocation(GameStrategyContext* gameStrategyContext) {
    gameStrategyContext->nearestLocation = getNearestLocationFromGameStrategyContext (gameStrategyContext);
}

GameTarget* findNextTarget(GameStrategyContext* gameStrategyContext) {
    updateGameStrategyContextNearestLocation(gameStrategyContext);

    // Find best Target, store LocationList in the context in currentTrajectory
    GameTarget* result = computeBestNextTarget(gameStrategyContext);
    gameStrategyContext->currentTarget = result;

    return result;
}

void updateTargetStatusAndScore(GameStrategyContext* gameStrategyContext) {
    GameTarget* currentTarget = gameStrategyContext->currentTarget;
    if (currentTarget == NULL) {
        return;
    }
    updateTargetStatus(currentTarget);
    if (currentTarget->status == TARGET_HANDLED) {
        currentTarget->gain = currentTarget->potentialGain;
        EndMatch* endMatch = gameStrategyContext->endMatch;
        if (endMatch == NULL) {
            writeError(ROBOT_END_MATCH_NULL);
            return;
        }
        gameStrategyContext->endMatch->scoreToShow += (int)currentTarget->gain;
    }
}


void executeTargetAction(GameStrategyContext* gameStrategyContext, GameTargetAction* targetAction) {
    GameTargetActionItemList* actionItemList = targetAction->actionItemList;
    if (executeTargetActionItemList(actionItemList, (int*)gameStrategyContext)) {
        // All Items of the actions were done successfully
        targetAction->status = ACTION_STATUS_DONE;
    }
    else {
        // We mark the action in error
        targetAction->status = ACTION_STATUS_ERROR;
    }
}

/**
* Handle the trajectory and return true if we go to a location, false else.
* @private
*/
bool handleNextMoveActionOrAction(GameStrategyContext* gameStrategyContext) {
    GameTarget* currentTarget = gameStrategyContext->currentTarget;
    // If No Target => No Action
    // Only manage Target which are available
    if (currentTarget == NULL || currentTarget->status != TARGET_AVAILABLE) {
        return false;
    }

    Navigation* navigation = gameStrategyContext->navigation;
    Location* nearestLocation = gameStrategyContext->nearestLocation;
    // Start Location could be null if the nearest Location was not found (because too far)
    if (nearestLocation == NULL) {
        // TODO : Find a Strategy to join a point if we are far from the nearest location (in case of Collision for example)
        return false;
    }

    // Compute the next action to do by priority
    GameTargetActionList* actionList = &(currentTarget->actionList);
    GameTargetAction* targetAction =  getNextGameTargetActionTodoByPriority(actionList);
    // Nothing more to do
    if (targetAction == NULL) {
        return false;
    }
    if (targetAction->endLocation == NULL || targetAction->endLocation == nearestLocation) {
        executeTargetAction(gameStrategyContext, targetAction);
        updateTargetStatusAndScore(gameStrategyContext);
        return true;
    }
    // We must compute via Drijska the next way to go to the end Location of the action
    else {
        computeBestPath(navigation, nearestLocation, targetAction->endLocation);
        // TODO : Manage the case where there is no way to go to endLocation
        return followComputedNextPath(gameStrategyContext);
    }

    return true;
}

bool nextStep(GameStrategyContext* gameStrategyContext) {
    // The start point is the nearest point of the robot
    // TODO : Restrict the nearest Point to the list of the trajectory to reach the target and not all locations ?
    updateGameStrategyContextNearestLocation(gameStrategyContext);

    // Launch command to follow the trajectory until the action location start
    if (handleNextMoveActionOrAction(gameStrategyContext)) {
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
    // During the move, we do nothing, we would evaluate next time if it has changed !
    if (trajectoryType != TRAJECTORY_TYPE_NONE) {
        return false;
    }
    // Always find a new target if no target is available
    GameTarget* currentTarget = gameStrategyContext->currentTarget;
    if (currentTarget == NULL || currentTarget->status == TARGET_HANDLED) {
        gameStrategyContext->currentTarget = NULL;
        findNextTarget(gameStrategyContext);
    }

    return nextStep(gameStrategyContext);
}
