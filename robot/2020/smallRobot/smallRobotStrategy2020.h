#ifndef SMALL_ROBOT_STRATEGY_2020_H
#define SMALL_ROBOT_STRATEGY_2020_H

#include "../../../robot/strategy/gameStrategyContext.h"

// SMALL ROBOT STRATEGY
#define SMALL_ROBOT_STRATEGY_2020_1_FLAG_1                      1
#define SMALL_ROBOT_STRATEGY_2020_2_FLAG_2                      2
#define SMALL_ROBOT_STRATEGY_2020_3_FLAG_2_REEF                 3

void initSmallRobotLocations2020(GameStrategyContext* gameStrategyContext);

void initSmallRobotPaths2020(GameStrategyContext* gameStrategyContext);

void initSmallRobotTargets2020(GameStrategyContext* gameStrategyContext);

void initSmallRobotTargetActions2020(GameStrategyContext* gameStrategyContext);

void initSmallRobotTargetActionsItems2020(GameStrategyContext* gameStrategyContext);

GameStrategy* initSmallRobotStrategiesItems2020(GameStrategyContext* gameStrategyContext);

void initSmallRobotStrategies2020(GameStrategyContext* gameStrategyContext);

#endif
