#include <stdlib.h>

#include "nextGameStrategyItemComputer.h"

#include "gameStrategy.h"
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

static LocationList* locationList;

static GameTarget* currentTarget;


GameTargetAction* getBestNextTarget(GameStrategy* gameStrategy,
								float elapsedMatchTime,
								Location* currentLocation,
								LocationList* outLocationList) {
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
			int distanceCost = computeBestPath(outLocationList, currentLocation, startLocation);
			// float gain = 0.0f; //targetGain(target, action, distance, elapsedMatchTime, 0.0, 0.0);
			// log(gainData, target, gain);
			int gain = distanceCost;
			if (gain > maxGain) {
				maxGain = gain;
				result = targetAction;
			}
		}
	}
	if (result != NULL) {
		// appendStringAndDec(getOutputStreamLogger(INFO), "cost=", cost);
		printGameTarget(getOutputStreamLogger(INFO), bestTarget);
	}
	return result;
}
