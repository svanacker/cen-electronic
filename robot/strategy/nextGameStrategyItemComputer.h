#ifndef NEXT_GAME_STRATEGY_ITEM_COMPUTER_H
#define NEXT_GAME_STRATEGY_ITEM_COMPUTER_H

#include "gameStrategy.h"
#include "gameStrategyContext.h"
#include "gameTarget.h"
#include "gameTargetAction.h"

#include "../../navigation/locationList.h"

/**
 * Computes the next targetAction depending on the game strategy Context.
 */
GameTargetAction* getBestNextTarget(GameStrategyContext* strategyContext);

#endif
