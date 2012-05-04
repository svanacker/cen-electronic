#include <stdlib.h>

#include "nextGameStrategyItemComputer.h"

#include "gameStrategy.h"
#include "gameStrategyItem.h"
#include "gameTarget.h"
#include "gameTargetAction.h"
#include "gameStrategyItem.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../navigation/navigation.h"
#include "../../navigation/locationList.h"

static LocationList* locationList;

GameTargetAction* getBestNextTarget(GameStrategy* gameStrategy,
								float elapsedMatchTime,
								Location* currentLocation,
								LocationList* outLocationList) {
	// Opponent opponent = RobotUtils.getRobotAttribute(Opponent.class, servicesProvider);

	float maxGain = 0.0f;
	GameTargetAction* result = NULL;
	// Loop on potential target
	// GameStrategyItemList* items = gameStrategy->items;
	// int size = getStrategyItemCount(items);
	int gameStrategyItemCount = 10;
	int i;
	for (i = 0; i < gameStrategyItemCount; i++) {
		GameStrategyItem* strategyItem = NULL; // TODO
		GameTarget* target = strategyItem->target;
		if (!target->available) {
			continue;
		}
		// getGainFunction* targetGain = item->gainFunction();
		int j;
		int targetActionCount = 10; // TODO
		for (j = 0; j < targetActionCount; j++) {
			GameTargetAction* targetAction = NULL;
			Location* startLocation = targetAction->startLocation;
			int distanceCost = computeBestPath(outLocationList, currentLocation, startLocation);
			float gain = 0.0f; //targetGain(target, action, distance, elapsedMatchTime, 0.0, 0.0);
			// log(gainData, target, gain);
			if (gain > maxGain) {
				maxGain = gain;
				result = targetAction;
				// TODO path.setValue(actionPath);
			}
		}
	}
	if (result != NULL) {
		/*
		appendStringAndDec(getOutputStreamLogger(INFO), "cost=", cost);
		gainData.append("<br>Best target: " + bestTarget.getTarget().toString());
		*/
	}
	return result;
}
