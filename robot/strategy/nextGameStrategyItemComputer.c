#include <stdlib.h>

#include "nextGameStrategyItemComputer.h"

#include "gameStrategy.h"
#include "gameTarget.h"
#include "gameTargetAction.h"
// #include "gameStrategyItemList.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../navigation/locationList.h"

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
	/*
	int i;
	for (i = 0; i < IGameStrategyItem item : items) {
		GameTarget* target = strategyItem->target;
		if (!target->available) {
			continue;
		}
		ITargetGain targetGain = item.getTargetGain();
		for (ITargetAction action : target) {
			List<Location> actionPath = getNavigationPath(currentLocation, action.getStartLocation(), cost);
			double distance = cost.getValue();
			double gain = targetGain.getGain(target, action, distance, elapsedMatchTime, opponent);
			log(gainData, target, gain);
			if (gain > maxGain) {
				maxGain = gain;
				bestTarget = action;
				path.setValue(actionPath);
			}
		}
	}
	if (bestTarget != null) {
		gainData.append("<br>Best target: " + bestTarget.getTarget().toString());
	}
	*/
	return result;
}
