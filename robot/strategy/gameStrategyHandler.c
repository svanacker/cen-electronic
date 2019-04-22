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

GameTarget* findNextTarget(GameStrategyContext* gameStrategyContext) {
    Navigation* navigation = gameStrategyContext->navigation;
    unsigned int targetHandledCount = getTargetHandledCount();
    if (targetHandledCount >= gameStrategyContext->maxTargetToHandle) {
        clearCurrentTarget(gameStrategyContext);
        return NULL;
    }

    // global points
    LocationList* navigationLocationList = getNavigationLocationList(navigation);

    Point* robotPosition = gameStrategyContext->robotPosition;

    // Find nearest location
    // The robot could not be exactly at the location, so we search the closest location
    float x = robotPosition->x;
    float y = robotPosition->y;
    gameStrategyContext->nearestLocation = getNearestLocation(navigationLocationList, x, y);

    // Find best Target, store LocationList in the context in currentTrajectory
    GameTarget* result = computeBestNextTarget(gameStrategyContext);
    gameStrategyContext->currentTarget = result;

    return result;
}

bool executeTargetActions(GameStrategyContext* gameStrategyContext) {
    markTargetInUse(gameStrategyContext);

    GameTargetAction* targetAction = gameStrategyContext->currentTargetAction;
    GameTargetActionItemList* actionItemList = targetAction->actionItemList;
    if (actionItemList == NULL) {
        markTargetAsHandled(gameStrategyContext);
        return false;
    }

    // There is actionItem in progress
    if (actionItemList != NULL && targetActionItemListHasNext(actionItemList)) {
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

/**
* Handle the trajectory and return true if we go to a location, false else.
* @private
*/
bool handleCurrentTrajectory(GameStrategyContext* gameStrategyContext) {
    LocationList* currentTrajectory = gameStrategyContext->currentTrajectory;

    if (currentTrajectory == NULL || currentTrajectory->size < 2) {
        // no more locations to reach
        clearLocationList(currentTrajectory);
        return false;
    }

    Location* start = getLocation(currentTrajectory, 0);
    Location* end = getLocation(currentTrajectory, 1);
    bool reversed;
    Navigation* navigation = gameStrategyContext->navigation;
    PathData* pathData = getPathOfLocations(getNavigationPathList(navigation), start, end, &reversed);

    // Follows the path
    if (!motionRotateToFollowPath(gameStrategyContext, pathData, reversed)) {
        motionFollowPath(gameStrategyContext, pathData, reversed);
        removeFirstLocation(currentTrajectory);
    }
    return true;
}

bool nextStep(GameStrategyContext* gameStrategyContext) {
    unsigned int counter = 0;
    while (true) {
        counter++;
        GameTargetAction* targetAction = gameStrategyContext->currentTargetAction;
    
        // If there is some locations
        if (getLocationCount(gameStrategyContext->currentTrajectory) != 0) {
            if (!handleCurrentTrajectory(gameStrategyContext)) {
                continue;
            }
            return true;
        }
        else if (targetAction != NULL) {
            if (!executeTargetActions(gameStrategyContext)) {
                // we will return on a different condition.
                continue;
            }
            return true;
        }
        else if (targetAction == NULL) {
            // no target, search a new one
            gameStrategyContext->currentTarget = findNextTarget(gameStrategyContext);
            if (gameStrategyContext->currentTarget == NULL) {
                clearCurrentTarget(gameStrategyContext);
                return false;
            }
            // Next target created a new current trajectory
            if (getLocationCount(gameStrategyContext->currentTrajectory) != 0) {
                if (!handleCurrentTrajectory(gameStrategyContext)) {
                    continue;
                }
                return true;
            }
        } else {
            if (!executeTargetActions(gameStrategyContext)) {
                // we will return on a different condition.
                continue;
            }
            return true;
        }
    }
    return true;
}

