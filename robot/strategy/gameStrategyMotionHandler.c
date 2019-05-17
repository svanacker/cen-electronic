#include "gameStrategyMotionHandler.h"

#include <math.h>
#include <stdlib.h>

#include "gameStrategyHandler.h"
#include "gameStrategyContext.h"
#include "nextGameStrategyItemComputer.h"

#include "../../common/error/error.h"

#include "../../common/math/cenMath.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerList.h"
#include "../../common/timer/timerConstants.h"

#include "../../motion/extended/bspline.h"
#include "../../motion/extended/bsplineList.h"

#include "../../navigation/location.h"
#include "../../navigation/locationList.h"
#include "../../navigation/locationListComputer.h"
#include "../../navigation/navigation.h"
#include "../../navigation/navigationComputer.h"
#include "../../navigation/path.h"
#include "../../navigation/pathList.h"

#include "../../client/motion/extended/clientExtendedMotion.h"
#include "../../client/motion/simple/clientMotion.h"
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
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*) timer->object;
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
                            TIME_DIVIDER_5_HERTZ,
                            &interruptGameStrategyMotionCallbackFunc,
                            "TIMER DELAY", 
							(int*) gameStrategyContext);
        timer->enabled = true;
}


bool updateRobotPositionFromMainBoardToMotorBoard(GameStrategyContext* gameStrategyContext) {
    Point* robotPosition = gameStrategyContext->robotPosition;
    return clientTrajectorySetAbsolutePosition(robotPosition->x, robotPosition->y, gameStrategyContext->robotAngleRadian);
}

void updateIfNeededRobotPositionFromMotorBoardToMainBoard(GameStrategyContext* gameStrategyContext) {
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

void clearCurrentTarget(GameStrategyContext* gameStrategyContext) {
    gameStrategyContext->currentTarget = NULL;
}

bool motionRotateToFollowPath(GameStrategyContext* gameStrategyContext, PathData* pathData) {
    if (pathData == NULL) {
        writeError(PATH_NULL);
        return false;
    }
    float angle = getPathStartAngleRadian(pathData);

    float diff = mod2PI(angle - gameStrategyContext->robotAngleRadian);
    if (fabs(diff) < degToRad(ANGLE_ROTATION_MIN_DEGREE)) {
        return false;
    }

    if (diff > 0.0f) {
        appendStringAndDecf(getDebugOutputStreamLogger(), "motionDriverLeft:", radToDeg(diff));
        println(getDebugOutputStreamLogger());
        // Simulate as if the robot goes to the position with a small error to be sure
        // that we do not rely the navigation on just exact computation
        if (gameStrategyContext->simulateMove) {
            gameStrategyContext->robotAngleRadian += diff + 0.001f;
        }
        else {
            motionDriverLeft(radToDeg(diff));
            gameStrategyContext->trajectoryType = TRAJECTORY_TYPE_ROTATION;
        }
    }
    else {
        appendStringAndDecf(getDebugOutputStreamLogger(), "motionDriverRight:", radToDeg(-diff));
        println(getDebugOutputStreamLogger());
        if (gameStrategyContext->simulateMove) {
            gameStrategyContext->robotAngleRadian += diff + 0.001f;
        }
        else {
            motionDriverRight(radToDeg(-diff));
            gameStrategyContext->trajectoryType = TRAJECTORY_TYPE_ROTATION;
        }
    }
    

    return true;
}

bool motionFollowPath(GameStrategyContext* gameStrategyContext, PathData* pathData) {
    if (pathData == NULL) {
        writeError(PATH_NULL);
        return false;
    }
    OutputStream* outputStream = getDebugOutputStreamLogger();
    appendString(outputStream, "motionFollowPath:");
    Location* location1 = pathData->location1;
    appendString(outputStream, location1->label);
    appendString(outputStream, "   ->   ");
    Location* location2 = pathData->location2;
    appendString(outputStream, location2->label);
    appendCRLF(outputStream);

    Location* location = pathData->location2;

    float angle = getPathEndAngleRadian(pathData);
    float cp1 = pathData->controlPointDistance1;
    float cp2 = pathData->controlPointDistance2;

    // Simulate as if the robot goes to the position with a small error to be sure that 
    // algorithm to find nearest position are ok
    if (gameStrategyContext->simulateMove) {
        gameStrategyContext->robotPosition->x = location->x + 1.0f;
        gameStrategyContext->robotPosition->y = location->y + 1.0f;
        gameStrategyContext->robotAngleRadian = angle;
    }
    else {
        clientExtendedMotionBSplineAbsolute(location->x, location->y, angle, cp1, cp2,
            pathData->accelerationFactor, pathData->speedFactor);
        if (cp1 < 0.0f) {
            gameStrategyContext->trajectoryType = TRAJECTORY_TYPE_BACKWARD;
        }
        else {
            gameStrategyContext->trajectoryType = TRAJECTORY_TYPE_FORWARD;
        }
    }
    return true;
}
