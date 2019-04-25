#include <math.h>
#include <stdlib.h>

#include "gameStrategyHandler.h"
#include "gameStrategyHandlerUtils.h"

#include "gameStrategyContext.h"

#include "nextGameStrategyItemComputer.h"

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
    Navigation* navigation = gameStrategyContext->navigation;
    unsigned int targetHandledCount = getTargetHandledCount();
    if (targetHandledCount >= gameStrategyContext->maxTargetToHandle) {
        clearCurrentTarget(gameStrategyContext);
        return NULL;
    }

    updateNearestLocation(gameStrategyContext);

    // Find best Target, store LocationList in the context in currentTrajectory
    GameTarget* result = computeBestNextTarget(gameStrategyContext);
    gameStrategyContext->currentTarget = result;

    return result;
}

bool executeTargetActionItemListForPhasis(GameStrategyContext* gameStrategyContext, GameTargetActionItemList* actionItemList, enum ActionItemPhasis phasis) {
    bool result = false;
    unsigned int actionItemIndex;
    // Loop on all action Items to do
    for (actionItemIndex = 0; actionItemIndex < actionItemList->size; actionItemIndex++) {
        GameTargetActionItem* actionItem = getGameTargetActionItem(actionItemList, actionItemIndex);
        // Do only action not done
        if (actionItem->status != ACTION_ITEM_STATUS_TODO) {
            continue;
        }

        // We only do the action Item at the right phasis (end or start) of action
        if (actionItem->phasis != phasis) {
            continue;
        }

        // Do the action item
        actionItem->actionItemFunction((int*)gameStrategyContext);
        actionItem->status = ACTION_ITEM_STATUS_DONE;
        result = true;
    }
    return result;
}

bool executeTargetActions(GameStrategyContext* gameStrategyContext) {
    GameTarget* currentTarget = gameStrategyContext->currentTarget;
    if (currentTarget == NULL) {
        return false;
    }
    GameTargetActionList* actionList = &(currentTarget->actionList);
    unsigned int actionIndex;

    // For All Actions
    for (actionIndex = 0; actionIndex < actionList->size; actionIndex++) {
        GameTargetAction* action = getGameTargetAction(actionList, actionIndex);

        // Do the action related to the start of Location
        GameTargetActionItemList* actionItemList = action->actionItemList;
        if (action->startLocation == gameStrategyContext->nearestLocation) {
            if (executeTargetActionItemListForPhasis(gameStrategyContext, actionItemList, ACTION_ITEM_PHASIS_START_LOCATION)) {
                return true;
            }
        }

        // Do the action related to the end of Location
        if (action->endLocation == gameStrategyContext->nearestLocation) {
            if (executeTargetActionItemListForPhasis(gameStrategyContext, actionItemList, ACTION_ITEM_PHASIS_END_LOCATION)) {
                return true;
            }
        }
    }
    return false;
}

/**
* Handle the trajectory of the robot to go from Action[0].startLocation -> Action[1].endLocation
* @private
*/
bool handleTrajectoryActions(GameStrategyContext* gameStrategyContext) {
    GameTarget* currentTarget = gameStrategyContext->currentTarget;
    if (currentTarget == NULL) {
        return false;
    }
    Navigation* navigation = gameStrategyContext->navigation;

    Location* robotLocation = gameStrategyContext->nearestLocation;
    // If the point of the robot is the same than the startLocation of the target Actions, we do not do anything
    if (robotLocation == currentTarget->startLocation) {
        return false;
    }
    // Take the next location to follow
    Location* end = robotLocation->resultNextLocation;
    // If the point is the same than the startLocation of the target Actions, we escape
    if (end == NULL || end == currentTarget->startLocation) {
        return false;
    }

    bool reversed;
    PathList* pathList = getNavigationPathList(navigation);
    PathData* pathData = getPathOfLocations(pathList, robotLocation, end, &reversed);

    // Check if to follow the path, we need to do first a rotation (to avoid problem on bSpline)
    if (!motionRotateToFollowPath(gameStrategyContext, pathData, reversed)) {
        // If this is not the case, we ask to follow the path
        motionFollowPath(gameStrategyContext, pathData, reversed);
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
    Navigation* navigation = gameStrategyContext->navigation;

    Location* robotLocation = gameStrategyContext->nearestLocation;
    // If the point of the robot is the same than the startLocation of the target Actions, we do not do anything
    if (robotLocation == currentTarget->startLocation) {
        return false;
    }
    // Take the next location to follow
    Location* end = robotLocation->resultNextLocation;
    // If the point is the same than the startLocation of the target Actions, we escape
    if (end == NULL || end == currentTarget->startLocation) {
        return false;
    }

    bool reversed;
    PathList* pathList = getNavigationPathList(navigation);
    PathData* pathData = getPathOfLocations(pathList, robotLocation, end, &reversed);

    // Check if to follow the path, we need to do first a rotation (to avoid problem on bSpline)
    if (!motionRotateToFollowPath(gameStrategyContext, pathData, reversed)) {
        // If this is not the case, we ask to follow the path
        motionFollowPath(gameStrategyContext, pathData, reversed);
    }
    return true;
}

bool nextStep(GameStrategyContext* gameStrategyContext) {
    // The start point is the nearest point of the robot
    // TODO : Restrict the nearest Point to the list of the trajectory to reach the target and not all locations ?
    updateNearestLocation(gameStrategyContext);

    // Launch command to follow the trajectory until the action location start
    if (handleTrajectoryToActionStart(gameStrategyContext)) {
        // We do not do anything, we wait that the robot reach his target
        return true;
    }

    // Launch command to follow the different actions (and move if action->endLocation != action->startLocation
    if (handleTrajectoryActions(gameStrategyContext)) {
        // We do not do anything, we wait that the robot reach his target
        return true;
    }

    // Launch command to execute the actions
    if (executeTargetActions(gameStrategyContext)) {
        return true;
    }

    return false;
}

/*
bool executeTargetActions(GameStrategyContext* gameStrategyContext) {
    // In progress on the target
    markTargetInUse(gameStrategyContext);

    GameTargetAction* targetAction = gameStrategyContext->currentTargetAction;
    // If no action Item List is defined
    GameTargetActionItemList* actionItemList = targetAction->actionItemList;
    if (actionItemList == NULL) {
        // We consider that the target was handled
        markTargetAsHandled(gameStrategyContext);
        return false;
    }

    // There is an actionItem in progress
    if (targetActionItemListHasNext(actionItemList)) {
        GameTargetActionItem* actionItem = targetActionItemListNext(actionItemList);

        // Do the action item
        actionItem->actionItemFunction((int*) gameStrategyContext);
        return true;
    }
    else {
        markTargetAsHandled(gameStrategyContext);
        // we do nothing more
        return false;
    }
    return true;
}
*/
