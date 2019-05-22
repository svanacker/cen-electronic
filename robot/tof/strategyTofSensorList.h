#ifndef STRATEGY_TOF_SENSOR_LIST_H
#define STRATEGY_TOF_SENSOR_LIST_H

#include "../../drivers/tof/tofList.h"

#include "../../robot/gameboard/gameboard.h"
#include "../../robot/match/startMatch.h"
#include "../../robot/strategy/gameStrategyContext.h"

/**
 * TOF MANAGEMENT
 * @param gameStrategyContext
 */
void handleTofSensorList(GameStrategyContext* gameStrategyContext, StartMatch* startMatch, TofSensorList* tofSensorList, GameBoard* gameBoard);

#endif
