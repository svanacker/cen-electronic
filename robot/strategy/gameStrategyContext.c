#include <stdlib.h>

#include "gameStrategyContext.h"

#include "../../common/timer/cenTimer.h"

/**
 * @private
 */
void initGameStrategyIndex(GameStrategyContext* gameStrategyContext) {
    RobotConfig* robotConfig = gameStrategyContext->robotConfig;
    unsigned int configValue = robotConfig->robotConfigReadInt(robotConfig);
    int strategyIndex = (configValue & CONFIG_STRATEGY_MASK);
    gameStrategyContext->strategyIndex = strategyIndex;
}

void initGameStrategyColor(GameStrategyContext* gameStrategyContext) {
    RobotConfig* robotConfig = gameStrategyContext->robotConfig;
    unsigned int configValue = robotConfig->robotConfigReadInt(robotConfig);

    if (configValue & CONFIG_COLOR_GREEN_MASK) {
        setColor(gameStrategyContext, TEAM_COLOR_GREEN);
    }
    else {
        setColor(gameStrategyContext, TEAM_COLOR_ORANGE);
    }
}

void initGameStrategyContext(GameStrategyContext* gameStrategyContext,
    RobotConfig* robotConfig,
    Navigation* navigation,
    Timer* strategyTimer,
    Point* robotPosition,
    Point* opponentRobotPosition,
    Point* lastObstaclePosition) {
    gameStrategyContext->navigation = navigation;
    gameStrategyContext->robotConfig = robotConfig;
    gameStrategyContext->strategyTimer = strategyTimer;
    gameStrategyContext->robotPosition = robotPosition;
    gameStrategyContext->opponentRobotPosition = opponentRobotPosition;
    gameStrategyContext->lastObstaclePosition = lastObstaclePosition;
    // Complex init
    initGameStrategyIndex(gameStrategyContext);


}
