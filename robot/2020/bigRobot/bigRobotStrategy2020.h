#ifndef BIG_ROBOT_STRATEGY_2020_H
#define BIG_ROBOT_STRATEGY_2020_H

#include "../../../robot/strategy/gameStrategyContext.h"

// SMALL ROBOT STRATEGY
#define BIG_ROBOT_STRATEGY_2020_1_SMALL_HARBOR                1
#define BIG_ROBOT_STRATEGY_2020_2_SMALL_HARBOR_LEFT_REEF      2

void initBigRobotLocations2020(GameStrategyContext* gameStrategyContext);

void initBigRobotPaths2020(GameStrategyContext* gameStrategyContext);

void initBigRobotTargets2020(GameStrategyContext* gameStrategyContext);

void initBigRobotTargetActions2020(GameStrategyContext* gameStrategyContext);

void initBigRobotTargetActionsItems2020(GameStrategyContext* gameStrategyContext);

GameStrategy* initBigRobotStrategiesItems2020(GameStrategyContext* gameStrategyContext);

void initBigRobotStrategies2020(GameStrategyContext* gameStrategyContext);

#endif
