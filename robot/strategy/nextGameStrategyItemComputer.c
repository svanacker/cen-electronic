#include <stdlib.h>

#include "nextGameStrategyItemComputer.h"

#include "gameStrategy.h"
#include "gameStrategyContext.h"
#include "gameStrategyItem.h"
#include "gameTarget.h"
#include "gameTargetAction.h"
#include "gameTargetActionList.h"
#include "gameStrategyItem.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../navigation/navigation.h"
#include "../../navigation/locationList.h"
#include "../../navigation/location.h"

GameTargetAction* getBestNextTarget(GameStrategyContext* strategyContext) {

	GameStrategy* gameStrategy = strategyContext->gameStrategy;
	// float elapsedMatchTime = strategyContext->elapsedMatchTime;
	Location* currentLocation = strategyContext->nearestLocation;

	// Opponent opponent = RobotUtils.getRobotAttribute(Opponent.class, servicesProvider);
	GameTarget* bestTarget = NULL;
	float maxGain = 0.0f;
	GameTargetAction* result = NULL;
	// Loop on potential target
	int strategyItemIndex;
	int gameStrategyItemCount = getStrategyItemCount(gameStrategy);
	for (strategyItemIndex = 0; strategyItemIndex < gameStrategyItemCount; strategyItemIndex++) {
		GameStrategyItem* strategyItem = getStrategyItem(gameStrategy, strategyItemIndex);
		
		GameTarget* target = strategyItem->target;
	
		if (!target->available) {
			continue;
		}
		// getGainFunction* targetGain = item->gainFunction();
		int actionIndex;
		GameTargetActionList* actionList = &(target->actionList);
		int targetActionCount = getGameTargetActionCount(actionList);
		for (actionIndex = 0; actionIndex < targetActionCount; actionIndex++) {
			GameTargetAction* targetAction = getGameTargetAction(actionList, actionIndex);
			Location* startLocation = targetAction->startLocation;
			int distanceCost = computeBestPath(&(strategyContext->currentTrajectory), currentLocation, startLocation);
			// float gain = 0.0f; //targetGain(target, action, distance, elapsedMatchTime, 0.0, 0.0);
			// log(gainData, target, gain);
			appendKeyAndName(getOutputStreamLogger(INFO), "start->location:", currentLocation->name);
			appendKeyAndName(getOutputStreamLogger(INFO), ", end->location:", startLocation->name);
			appendKeyAndName(getOutputStreamLogger(INFO), ", target:", target->name);
			appendStringAndDec(getOutputStreamLogger(INFO), ", distanceCost=", distanceCost);
			println(getOutputStreamLogger(INFO));

			if (distanceCost == MAX_COST) {
				continue;
			}
			float gain = 1000.0f / (float) distanceCost;
			if (gain > maxGain) {
				maxGain = gain;
				result = targetAction;
				bestTarget = target;
			}
		}
	}
	if (result != NULL) {
		appendStringAndDecf(getOutputStreamLogger(INFO), "cost=", maxGain);
		printGameTarget(getOutputStreamLogger(INFO), bestTarget);
		printLocationList(getOutputStreamLogger(INFO), ", currentTrajectory:", &(strategyContext->currentTrajectory));
	}
	return result;
}
