#include <stdlib.h>

#include "gameStrategyContext.h"
#include "teamColor.h"

#include "../../common/timer/cenTimer.h"

#include "../../common/log/logger.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

/**
 * @private
 */
void initGameStrategyIndex(GameStrategyContext* gameStrategyContext) {
    RobotConfig* robotConfig = gameStrategyContext->robotConfig;
    unsigned int configValue = robotConfig->robotConfigReadInt(robotConfig);
    int strategyIndex = (configValue & CONFIG_STRATEGY_MASK);
    gameStrategyContext->strategyIndex = strategyIndex;
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

void showGameStrategyContextTeamColor(GameStrategyContext* gameStrategyContext) {
    OutputStream* outputStream = getAlwaysOutputStreamLogger();
    appendTeamColorAsString(outputStream, gameStrategyContext->color);
    println(outputStream);
}