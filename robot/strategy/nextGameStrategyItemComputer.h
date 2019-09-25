#ifndef NEXT_GAME_STRATEGY_ITEM_COMPUTER_H
#define NEXT_GAME_STRATEGY_ITEM_COMPUTER_H

#include "gameStrategy.h"
#include "gameStrategyContext.h"
#include "gameTarget.h"
#include "gameTargetAction.h"

#include "../../navigation/locationList.h"

// Define if we want to debug the next Game Strategy
// #define NEXT_GAME_STRATEGY_ITEM_COMPUTER_DEBUG

/**
 * Computes the next targetAction depending on the game strategy Context.
 */
GameTarget* computeBestNextTarget(GameStrategyContext* strategyContext);

#endif
