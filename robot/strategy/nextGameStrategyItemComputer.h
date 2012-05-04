#ifndef NEXT_GAME_STRATEGY_ITEM_COMPUTER_H
#define NEXT_GAME_STRATEGY_ITEM_COMPUTER_H

#include "gameStrategy.h"
#include "gameTarget.h"
#include "gameTargetAction.h"

#include "../../navigation/locationList.h"

GameTargetAction* getBestNextTarget(GameStrategy* gameStrategy,
								float elapsedMatchTime,
								Location* currentLocation,
								LocationList* outLocationList);

#endif
