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
#include "../../robot/strategy/gameStrategyOutsidePathHandler.h"
#include "../../robot/strategy/gameStrategyMotionHandler.h"
#include "../../robot/strategy/gameStrategyPositionHandler.h"
#include "../../robot/strategy/gameTargetActionList.h"
#include "../../robot/strategy/gameTargetAction.h"
#include "../../robot/strategy/gameStrategyContext.h"
#include "../../robot/strategy/nextGameStrategyItemComputer.h"

#include "../../robot/robot.h"

void initStrategyHandler(GameStrategyContext* gameStrategyContext) {
}

Location* updateGameStrategyContextNearestLocation(GameStrategyContext* gameStrategyContext) {
    if (isLoggerTraceEnabled()) {
        appendStringLN(getTraceOutputStreamLogger(), "updateGameStrategyContextNearestLocation");
    }
    gameStrategyContext->nearestLocation = getNearestLocationFromGameStrategyContext(gameStrategyContext);
    if (isLoggerTraceEnabled()) {
        appendString(getTraceOutputStreamLogger(), "gameStrategyContext->nearestLocation=");
        if (gameStrategyContext->nearestLocation != NULL) {
            appendFixedCharArray(getTraceOutputStreamLogger(), &(gameStrategyContext->nearestLocation->name));
            appendCRLF(getTraceOutputStreamLogger());
        }
        else {
            appendStringLN(getTraceOutputStreamLogger(), "NULL");
        }
    }
    return gameStrategyContext->nearestLocation;
}

GameTarget* findNextTarget(GameStrategyContext* gameStrategyContext) {
    if (isLoggerTraceEnabled()) {
        appendStringLN(getTraceOutputStreamLogger(), "findNextTarget");
    }
    updateGameStrategyContextNearestLocation(gameStrategyContext);

    // Find best Target, store LocationList in the context in currentTrajectory
    GameTarget* result = computeBestNextTarget(gameStrategyContext);
    gameStrategyContext->currentTarget = result;

    return result;
}

void updateTargetStatusAndScore(GameStrategyContext* gameStrategyContext) {
    if (isLoggerTraceEnabled()) {
        appendStringLN(getTraceOutputStreamLogger(), "updateTargetStatusAndScore");
    }
    GameTarget* currentTarget = gameStrategyContext->currentTarget;
    if (currentTarget == NULL) {
        return;
    }
    updateTargetStatus(currentTarget);
    if (currentTarget->status == TARGET_HANDLED) {
        // We consider that if the target was handled, we could compute the gain as the "potential gain"
        currentTarget->gain = currentTarget->potentialGain;
        EndMatch* endMatch = gameStrategyContext->endMatch;
        if (endMatch == NULL) {
            writeError(ROBOT_END_MATCH_NULL);
            return;
        }
        gameStrategyContext->endMatch->scoreToShow += (int) currentTarget->gain;
    }
}

void executeTargetAction(GameStrategyContext* gameStrategyContext, GameTargetAction* targetAction) {
    if (isLoggerTraceEnabled()) {
        appendStringLN(getTraceOutputStreamLogger(), "executeTargetAction");
    }
    GameTargetActionItemList* actionItemList = targetAction->actionItemList;
    targetAction->status = executeTargetActionItemList(actionItemList, (int*) gameStrategyContext);
}

/**
 * Handle the trajectory and return true if we go to a location, false else.
 * @private
 */
bool handleNextMoveActionOrAction(GameStrategyContext* gameStrategyContext) {
    if (isLoggerTraceEnabled()) {
        appendStringLN(getTraceOutputStreamLogger(), "handleNextMoveActionOrAction");
    }
    GameTarget* currentTarget = gameStrategyContext->currentTarget;
    // If No Target => No Action
    // Only manage Target which are available
    if (currentTarget == NULL) {
        if (isLoggerTraceEnabled()) {
            appendStringLN(getTraceOutputStreamLogger(), "currentTarget=NULL");
        }
        return false;
    }
    /*
    if (currentTarget->status == TARGET_MISSED || currentTarget->status == TARGET_MISSED) {
        if (isLoggerTraceEnabled()) {
            appendStringLN(getTraceOutputStreamLogger(), "currentTarget->status != TARGET_AVAILABLE");
        }
        return false;
    }
    */
    Location* nearestLocation = gameStrategyContext->nearestLocation;
    Navigation* navigation = gameStrategyContext->navigation;

    // If the robot was stopped during a target research, and that we are away from a point, we create new temporary point
    // to escape
    if (nearestLocation == NULL && TRAJECTORY_TYPE_NONE == gameStrategyContext->trajectoryType) {
        // Start Location could be null if the nearest Location was not found (because too far)
        gameStrategyCreateOutsideTemporaryPaths(gameStrategyContext);
        // We have a new temporary location where the robot is !
        nearestLocation = updateGameStrategyContextNearestLocation(gameStrategyContext);
    }
    else {
        // Try to recycle the temporary Paths & Locations !
        gameStrategyClearOusideTemporaryPathsAndLocations(gameStrategyContext);
    }

    // Compute the next action to do by priority
    GameTargetActionList* actionList = &(currentTarget->actionList);
    GameTargetAction* targetAction = getNextGameTargetActionTodoByPriority(actionList);
    // Nothing more to do
    if (targetAction == NULL) {
        return false;
    }
    if (targetAction->endLocation == NULL || targetAction->endLocation == nearestLocation) {
        executeTargetAction(gameStrategyContext, targetAction);
        updateTargetStatusAndScore(gameStrategyContext);
        return true;
    }// We must compute via Drijska the next way to go to the end Location of the action
    else {
        computeBestPath(navigation, nearestLocation, targetAction->endLocation);
        // TODO : Manage the case where there is no way to go to endLocation
        return followComputedNextPath(gameStrategyContext);
    }

    return true;
}

bool nextStep(GameStrategyContext* gameStrategyContext) {
    if (isLoggerTraceEnabled()) {
        appendStringLN(getTraceOutputStreamLogger(), "nextStep");
    }
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
    if (TRAJECTORY_TYPE_NONE != trajectoryType) {
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
