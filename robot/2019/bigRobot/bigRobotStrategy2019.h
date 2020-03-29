#ifndef BIG_ROBOT_STRATEGY_2019_H
#define BIG_ROBOT_STRATEGY_2019_H

#include "../../../robot/strategy/gameStrategyContext.h"

// BIG ROBOT STRATEGY
#define BIG_ROBOT_STRATEGY_1_CHAOS                                             1
#define BIG_ROBOT_STRATEGY_2_BIG_DISTRIBUTOR_LINE_1                            2
#define BIG_ROBOT_STRATEGY_3_BIG_DISTRIBUTOR_LINE_1_2_3                        3
#define BIG_ROBOT_STRATEGY_4_CHAOS_BIG_DISTRIBUTOR_LINE                        4
#define BIG_ROBOT_STRATEGY_5_CHAOS_BIG_DISTRIBUTOR_LINE                        5
#define BIG_ROBOT_STRATEGY_6_CHAOS_BIG_DISTRIBUTOR_LINE                        6

void initBigRobotLocations2019(GameStrategyContext* gameStrategyContext);

void initBigRobotPaths2019(GameStrategyContext* gameStrategyContext);

void initBigRobotTargets2019(GameStrategyContext* gameStrategyContext);

void initBigRobotTargetActions2019(GameStrategyContext* gameStrategyContext);

void initBigRobotTargetActionsItems2019(GameStrategyContext* gameStrategyContext);

GameStrategy* initBigRobotStrategiesItems2019(GameStrategyContext* gameStrategyContext);

void initBigRobotStrategies2019(GameStrategyContext* gameStrategyContext);

#endif
