#include <stdlib.h>

#include "nextGameStrategyItemComputer.h"

#include "gameStrategy.h"
#include "gameStrategyContext.h"
#include "gameStrategyItem.h"
#include "gameTarget.h"
#include "gameTargetAction.h"
#include "gameTargetActionList.h"
#include "gameStrategyItem.h"

#include "../../common/commons.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../navigation/navigation.h"
#include "../../navigation/navigationComputer.h"
#include "../../navigation/locationList.h"
#include "../../navigation/location.h"

GameTarget* computeBestNextTarget(GameStrategyContext* strategyContext) {
    GameTarget* result = NULL;
    GameStrategy* gameStrategy = strategyContext->gameStrategy;
    if (gameStrategy == NULL) {
        return NULL;
    }
    Navigation* navigation = strategyContext->navigation;

    float maxOpportunityFactor = -1.0f;
    // Loop on potential target
    int strategyItemIndex;
    int gameStrategyItemCount = getStrategyItemCount(gameStrategy);

    // Loop every StrategyItem with Target
    for (strategyItemIndex = 0; strategyItemIndex < gameStrategyItemCount; strategyItemIndex++) {
        GameStrategyItem* strategyItem = getStrategyItem(gameStrategy, strategyItemIndex);
        
        GameTarget* target = strategyItem->target;
        if (target == NULL) {
            writeError(TARGET_IS_NULL);
            continue;
        }
        // Don't handle it if not available
        if (target->status != TARGET_AVAILABLE) {
            continue;
        }
        // getGainFunction* targetGain = item->gainFunction();
        int actionIndex;
        GameTargetActionList* actionList = &(target->actionList);
        int targetActionCount = getGameTargetActionCount(actionList);

        // To avoid DIVIDE_BY_ZERO Error, we consider that the base cost is 1.0f
        float cost = 1.0f;  

        // For every Action of the target, compute the cost
        for (actionIndex = 0; actionIndex < targetActionCount; actionIndex++) {

            GameTargetAction* targetAction = getGameTargetAction(actionList, actionIndex);
            Location* startLocation = targetAction->startLocation;
            Location* endLocation = targetAction->endLocation;

            // Add the equivalent of timeToAchieve with cost (could vary because the speed / acceleration factor could be change)
            // TODO : Manage the equivalence factor : 1 second = equivalent of going a cost of 500.0f
            cost += 500.0f * targetAction->timeToAchieve;

            if (startLocation == NULL) {
                continue;
            }

            // First, we compute the cost to go to the beginning of the start Location of the first action
            if (actionIndex == 0) {
                cost += computeBestPath(navigation, strategyContext->nearestLocation, startLocation);
            }

            if (endLocation == NULL) {
                continue;
            }

            // Add the cost of each moving to do the action
            cost += computeBestPath(navigation, startLocation, endLocation);

            if (cost >= MAX_COST) {
                continue;
            }
        }
        // The opportunity is the gain divide by the cost
        target->currentComputedOpportunityFactor = 1000.0f * (target->potentialGain / cost);

        // Find the max opportunity
        if (target->currentComputedOpportunityFactor > maxOpportunityFactor) {
            maxOpportunityFactor = target->currentComputedOpportunityFactor;
            result = target;
        }
    }
    return result;
}
