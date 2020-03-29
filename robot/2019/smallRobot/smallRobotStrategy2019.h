#ifndef SMALL_ROBOT_STRATEGY_2019_H
#define SMALL_ROBOT_STRATEGY_2019_H

#include "../../../robot/strategy/gameStrategyContext.h"

// SMALL ROBOT STRATEGY
#define SMALL_ROBOT_STRATEGY_1_ACCELERATOR                                     1
#define SMALL_ROBOT_STRATEGY_2_ACCELERATOR_TAKE_GOLDENIUM                      2
#define SMALL_ROBOT_STRATEGY_3_ACCELERATOR_TAKE_DROP_GOLDENIUM                 3
#define SMALL_ROBOT_STRATEGY_4_ACCELERATOR_TAKE_DROP_GOLDENIUM_SMALL_DIST      4
#define SMALL_ROBOT_STRATEGY_5_ACCELERATOR_CENTER_GOLDENIUM_SMALL_DIST         5
#define SMALL_ROBOT_STRATEGY_6_ACCELERATOR_CENTER_GOLDENIUM_REDIUM_GREENIUM    6

void initSmallRobotLocations2019(GameStrategyContext* gameStrategyContext);

void initSmallRobotPaths2019(GameStrategyContext* gameStrategyContext);

void initSmallRobotTargets2019(GameStrategyContext* gameStrategyContext);

void initSmallRobotTargetActions2019(GameStrategyContext* gameStrategyContext);

void initSmallRobotTargetActionsItems2019(GameStrategyContext* gameStrategyContext);

GameStrategy* initSmallRobotStrategiesItems2019(GameStrategyContext* gameStrategyContext);

void initSmallRobotStrategies2019(GameStrategyContext* gameStrategyContext);

#endif
