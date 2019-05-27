#include "gameStrategyPositionHandler.h"

#include <math.h>
#include <stdlib.h>

#include "gameStrategyHandler.h"
#include "gameStrategyContext.h"

#include "../../common/error/error.h"

#include "../../common/math/cenMath.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerList.h"
#include "../../common/timer/timerConstants.h"

#include "../../navigation/location.h"
#include "../../navigation/locationList.h"
#include "../../navigation/locationListComputer.h"
#include "../../navigation/navigation.h"
#include "../../navigation/navigationComputer.h"
#include "../../navigation/path.h"
#include "../../navigation/pathList.h"

#include "../../client/motion/position/clientTrajectory.h"

#include "../../robot/strategy/gameTargetList.h"
#include "../../robot/robot.h"

/**
 * @private / Callback
 */
void interruptGameStrategyMotionCallbackFunc(Timer* timer) {
    if (timer == NULL) {
        writeError(TIMER_NULL);
        return;
    }
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*)timer->object;
    if (gameStrategyContext == NULL) {
        writeError(TIMER_OBJECT_NULL);
        return;
    }

    // We don't will ask the position to the motor Board if the robot is not 
    // moving
    enum TrajectoryType trajectoryType = gameStrategyContext->trajectoryType;
    if (trajectoryType == TRAJECTORY_TYPE_NONE) {
        return;
    }

    gameStrategyContext->robotPositionToUpdateInterruptFlag = true;
}

void initGameStrategyMotionHandler(GameStrategyContext* gameStrategyContext) {
    Timer* timer = addTimer(TIMER_STRATEGY_MOTION_HANDLER_UPDATE_ROBOT_POSITION,
        TIME_DIVIDER_3_HERTZ,
        &interruptGameStrategyMotionCallbackFunc,
        "MOTION UPDATE",
        (int*)gameStrategyContext);
    timer->enabled = true;
}


bool updateRobotPositionFromMainBoardToMotorBoard(GameStrategyContext* gameStrategyContext) {
    if (gameStrategyContext == NULL) {
        writeError(GAME_STRATEGY_CONTEXT_NULL);
        return false;
    }
    Point* robotPosition = gameStrategyContext->robotPosition;
    if (robotPosition == NULL) {
        writeError(ROBOT_POSITION_NULL);
        return false;
    }
    return clientTrajectorySetAbsolutePosition(robotPosition->x, robotPosition->y, gameStrategyContext->robotAngleRadian);
}

void updateIfNeededRobotPositionFromMotorBoardToMainBoard(GameStrategyContext* gameStrategyContext) {
    // We do not update the robot Position by pulling, but by notification !
    return;
    // To avoid to continously ask the position
    if (!gameStrategyContext->robotPositionToUpdateInterruptFlag) {
        return;
    }
    // Update the position from the MOTOR BOARD. If we don't do it,
    // The board keep the original value from the latest move
    // TODO : Clarify the usage of Robot Position
    RobotPosition robotPosition;
    clientTrajectoryUpdateRobotPosition(&robotPosition);
    gameStrategyContext->robotPosition->x = robotPosition.x;
    gameStrategyContext->robotPosition->y = robotPosition.y;
    gameStrategyContext->robotAngleRadian = robotPosition.angleRadian;

    // To avoid to continously ask the position, the flag will be changed by a frequent timer interruption
    gameStrategyContext->robotPositionToUpdateInterruptFlag = false;

}

Location* getNearestLocationFromGameStrategyContext(GameStrategyContext* gameStrategyContext) {
    Navigation* navigation = gameStrategyContext->navigation;
    LocationList* navigationLocationList = getNavigationLocationList(navigation);

    Point* robotPosition = gameStrategyContext->robotPosition;

    // Find nearest location
    // The robot could not be exactly at the location, so we search the closest location
    float x = robotPosition->x;
    float y = robotPosition->y;
    return getNearestLocation(navigationLocationList, x, y, MAX_DISTANCE_NEAREST_LOCATION);
}
