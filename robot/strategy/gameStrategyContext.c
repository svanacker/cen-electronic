#include <stdlib.h>

#include "gameStrategyContext.h"

#include "../../common/timer/cenTimer.h"


void initGameStrategyContext(GameStrategyContext* gameStrategyContext,
    Navigation* navigation,
    Timer* strategyTimer,
    Point* robotPosition,
    Point* opponentRobotPosition,
    Point* lastObstaclePosition) {
    gameStrategyContext->navigation = navigation;
    gameStrategyContext->strategyTimer = strategyTimer;
    gameStrategyContext->robotPosition = robotPosition;
    gameStrategyContext->opponentRobotPosition = opponentRobotPosition;
    gameStrategyContext->lastObstaclePosition = lastObstaclePosition;
}
