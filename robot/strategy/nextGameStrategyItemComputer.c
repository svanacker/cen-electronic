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

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../navigation/navigation.h"
#include "../../navigation/locationList.h"
#include "../../navigation/location.h"

void computeBestNextTarget(GameStrategyContext* strategyContext) {

    GameStrategy* gameStrategy = strategyContext->gameStrategy;
    // float elapsedMatchTime = strategyContext->elapsedMatchTime;
    Location* currentLocation = strategyContext->nearestLocation;

    // Opponent opponent = RobotUtils.getRobotAttribute(Opponent.class, servicesProvider);
    float maxGain = 0.0f;
    // Loop on potential target
    int strategyItemIndex;
    int gameStrategyItemCount = getStrategyItemCount(gameStrategy);
    for (strategyItemIndex = 0; strategyItemIndex < gameStrategyItemCount; strategyItemIndex++) {
        GameStrategyItem* strategyItem = getStrategyItem(gameStrategy, strategyItemIndex);
        
        GameTarget* target = strategyItem->target;
    
        if (target->status != TARGET_AVAILABLE) {
            continue;
        }
        // getGainFunction* targetGain = item->gainFunction();
        int actionIndex;
        GameTargetActionList* actionList = &(target->actionList);
        int targetActionCount = getGameTargetActionCount(actionList);
        for (actionIndex = 0; actionIndex < targetActionCount; actionIndex++) {
            GameTargetAction* targetAction = getGameTargetAction(actionList, actionIndex);
            Location* startLocation = targetAction->startLocation;
            float distanceCost = computeBestPath(currentLocation, startLocation);
            
            // LOG costs
            //printLocationList(getInfoOutputStreamLogger(), "Result=", &(strategyContext->currentTrajectory));

            // float gain = 0.0f; //targetGain(target, action, distance, elapsedMatchTime, 0.0, 0.0);
            // log(gainData, target, gain);

            #ifdef NEXT_GAME_STRATEGY_ITEM_COMPUTER_DEBUG
                OutputStream outputStream = getInfoOutputStreamLogger();
                appendKeyAndName(outputStream, "start->location:", currentLocation->name);
                appendKeyAndName(outputStream, ", end->location:", startLocation->name);
                appendKeyAndName(outputStream, ", target:", target->name);
                appendStringAndDec(outputStream, ", distanceCost=", distanceCost);
                println(outputStream);
            #endif

            if (distanceCost >= MAX_COST) {
                continue;
            }
            float gain = 1000.0f / distanceCost;
            if (gain > maxGain) {
                maxGain = gain;
                strategyContext->currentTargetAction = targetAction;
                strategyContext->currentTarget = target;
            }
        }
    }

    // updates the trajectory to fit to the best target
    GameTargetAction* targetAction = strategyContext->currentTargetAction;
    if (targetAction != NULL) {
        Location* startLocation = targetAction->startLocation;
        computeBestPath(currentLocation, startLocation);
        // TODO : printLocationLinkedPath(getInfoOutputStreamLogger(), "Result=", &(strategyContext->currentTrajectory));
    }

    #ifdef NEXT_GAME_STRATEGY_ITEM_COMPUTER_DEBUG
        if (strategyContext->targetAction != NULL) {
            OutputStream outputStream = getInfoOutputStreamLogger();
            appendStringAndDecf(outputStream, "cost=", maxGain);
            printGameTarget(outputStream, bestTarget, false);
            printLocationList(outputStream, ", currentTrajectory:", &(strategyContext->currentTrajectory));
        }
    #endif
}
