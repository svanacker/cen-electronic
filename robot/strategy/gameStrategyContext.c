#include <stdlib.h>

#include "gameStrategyContext.h"
#include "gameStrategyMotionHandler.h"
#include "teamColor.h"

#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerList.h"
#include "../../common/timer/timerConstants.h"

#include "../../common/log/logger.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../drivers/tof/tofList.h"

#include "../../motion/motionConstants.h"

/**
 * @private
 */
void initGameStrategyIndex(GameStrategyContext* gameStrategyContext) {
    RobotConfig* robotConfig = gameStrategyContext->robotConfig;
    unsigned int configValue = robotConfig->robotConfigReadInt(robotConfig);
    // If config == 0 ==> No Strategy (free to use by UART Command)
    // Mask = 0b001 => Strategy 1, but we use 0 based array => 0
    unsigned int strategyMask = (configValue & CONFIG_STRATEGY_MASK);
    if (strategyMask == 0) {
        gameStrategyContext->strategyId = NO_STRATEGY_INDEX;
    }
    else {
        gameStrategyContext->strategyId = strategyMask;
    }
}

void obstacleTimerCallbackFunc(Timer* timer) {
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*) timer->object;
    Navigation* navigation = gameStrategyContext->navigation;
    PathList* pathList = navigation->paths;

    pathListDecreaseObstacleCost(pathList);
}


void initGameStrategyContext(GameStrategyContext* gameStrategyContext,
    RobotConfig* robotConfig,
    Navigation* navigation,
    EndMatch* endMatch,
    TofSensorList* tofSensorList,
    Point* robotPosition,
    Point* opponentRobotPosition,
    Point* lastObstaclePosition,
    ServoList* servoList) {
    gameStrategyContext->navigation = navigation;
    gameStrategyContext->robotConfig = robotConfig;
    gameStrategyContext->endMatch = endMatch;
    gameStrategyContext->tofSensorList = tofSensorList;
    gameStrategyContext->servoList = servoList;
    gameStrategyContext->robotPosition = robotPosition;
    gameStrategyContext->opponentRobotPosition = opponentRobotPosition;
    gameStrategyContext->lastObstaclePosition = lastObstaclePosition;
    // Config
    gameStrategyContext->defaultAccelerationFactor = 1.0f;
    gameStrategyContext->defaultSpeedFactor = 1.0f;
    gameStrategyContext->loopTargetAndActions = !isConfigSet(robotConfig, CONFIG_STRATEGY_MANUAL_MODE);

    // Timer Init
    Timer* obstacleTimer = addTimer(ROBOT_OBSTACLE_TIMER_CODE, TIME_DIVIDER_1_HERTZ, &obstacleTimerCallbackFunc, "OBSTACLE TIMER", (int*) gameStrategyContext);
    gameStrategyContext->obstacleTimer = obstacleTimer;
    if (obstacleTimer != NULL) {
        obstacleTimer->callback = obstacleTimerCallbackFunc;
    }

    // Position Management
    initGameStrategyMotionHandler(gameStrategyContext);

    // Complex init
    initGameStrategyIndex(gameStrategyContext);
}

void showGameStrategyContextTeamColorAndStrategy(GameStrategyContext* gameStrategyContext) {
    OutputStream* outputStream = getAlwaysOutputStreamLogger();
    // COLOR
    appendTeamColorAsString(outputStream, gameStrategyContext->color);
    // STRATEGY
    appendString(outputStream, ",STG:");
    appendDec(outputStream, gameStrategyContext->strategyId);
    // SPEED
    appendString(outputStream, ",SPEED:");
    RobotConfig* robotConfig = gameStrategyContext->robotConfig;
    unsigned int speedIndex = (robotConfig->robotConfigReadInt(robotConfig) & CONFIG_SPEED_MASK) >> CONFIG_SPEED_SHIFT_BIT_VALUE;
    appendDec(outputStream, speedIndex);
    // TOF
    unsigned int sonarIndex = (robotConfig->robotConfigReadInt(robotConfig) & CONFIG_SONAR_MASK) >> CONFIG_SONAR_SHIFT_BIT_VALUE;
    appendString(outputStream, "TOF:");
    appendDec(outputStream, sonarIndex);
    appendSpace(outputStream);    
}