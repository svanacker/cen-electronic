#include "gameStrategyCollisionHandler.h"

#include <math.h>
#include <stdlib.h>

#include "gameStrategyHandler.h"

#include "gameStrategyContext.h"

#include "nextGameStrategyItemComputer.h"

#include "../../common/math/cenMath.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerList.h"

#include "../../client/motion/simple/clientMotion.h"

#include "../../motion/extended/bspline.h"
#include "../../motion/extended/bsplineList.h"

#include "../../navigation/location.h"
#include "../../navigation/locationList.h"
#include "../../navigation/locationListComputer.h"
#include "../../navigation/navigation.h"
#include "../../navigation/navigationComputer.h"
#include "../../navigation/path.h"
#include "../../navigation/pathList.h"

#include "../../robot/strategy/gameTargetList.h"
#include "../../robot/robot.h"

bool isColliding(Point* path, Point* obstacle) {
    float d = distanceBetweenPoints(path, obstacle);
    bool result = (d < DISTANCE_OPPONENT_TO_PATH);
    return result;
}

bool isValidLocation(Point* p) {
    // TODO : To Check
    return (!floatEqualsZero(p->x) && !floatEqualsZero(p->y));
}

/**
 * Loop on a pathData, to know if the path has an intersection with the opponentRobotPosition.
 * @private
 */
bool isPathAvailable(GameStrategyContext* gameStrategyContext, PathData* pathData, BSplineCurve* curve) {
    if (curve == NULL) {
        return true;
    }
    float angle1 = getPathStartAngleRadian(pathData);
    float angle2 = getPathEndAngleRadian(pathData);
    parameterBSplineWithDistanceAndAngle(curve,
                                         pathData->location1->x,
                                         pathData->location1->y,
                                         angle1, 
                                         pathData->location2->x,
                                         pathData->location2->y,
                                         angle2,
                                         pathData->controlPointDistance1, 
                                         pathData->controlPointDistance2,
                                         curve->accelerationFactor,
                                         curve->speedFactor,
                                         false);

    Point p;
    Point* opponentRobotPosition = gameStrategyContext->opponentRobotPosition;
    Point* lastObstaclePosition = gameStrategyContext->lastObstaclePosition;
    bool opponentPresent = isValidLocation(opponentRobotPosition);
    bool obstaclePresent = isValidLocation(lastObstaclePosition);
    float i;
    // 20  Sample = 0.05f for Step
    for (i = 0.0f; i < 1.0f; i += 0.05f) {
        computeBSplinePoint(curve, i, &p);
        // checking opponent
        if (opponentPresent && isColliding(&p, opponentRobotPosition)) {
            return false;
        }
        // checking last obstacle
        if (obstaclePresent && isColliding(&p, lastObstaclePosition)) {
            return false;
        }
    }
    return true;
}

bool mustComputePaths(GameStrategyContext* gameStrategyContext) {
    Point* opponentRobotPosition = gameStrategyContext->opponentRobotPosition;
    Point* lastObstaclePosition = gameStrategyContext->lastObstaclePosition;
    bool opponentPresent = isValidLocation(opponentRobotPosition);
    bool obstaclePresent = isValidLocation(lastObstaclePosition);

    return opponentPresent || obstaclePresent;

    // TODO
    // Case when the robot position is detected himself as the opponent robot !!!
    // All paths will be marked as unavailable, but the robot will try the path even (cost is only more huge)
}

void updatePathsAvailability(GameStrategyContext* gameStrategyContext) {
#ifdef DEBUG_OPPONENT_ROBOT
    OutputStream* logStream = getInfoOutputStreamLogger();
    println(logStream);
    appendString(logStream, "Updating available paths");
    //    printGameStrategyContext(logStream, getStrategyContext());
#endif

    bool computePath = mustComputePaths(gameStrategyContext);
    if (!computePath) {
        println(logStream);
        appendString(logStream, "Don't compute Path !");
    }
    Navigation* navigation = gameStrategyContext->navigation;
    PathList* paths = getNavigationPathList(navigation);
    unsigned int i;
    for (i = 0; i < paths->size; i++) {
        PathData* pathData = getPath(paths, i);
        // by default, path is available
        bool available = true;
        // Don't do the compute if it's not necessary
        if (computePath) {
            available = isPathAvailable(gameStrategyContext, pathData, NULL);
        }
        setPathAvailability(navigation, i, available);
    }

#ifdef DEBUG_OPPONENT_ROBOT
    // LOG
    unsigned int k;
    for (k = 0; k < paths->size; k++) {
        PathData* pathData = getPath(paths, k);
        if (!getPathAvailability(navigation, k)) {
            println(logStream);
            appendString(logStream, pathData->location1->name);
            appendString(logStream, "->");
            appendString(logStream, pathData->location2->name);
            appendString(logStream, ": UNAVAILABLE");
        }
    }
    println(logStream);
#endif
}

void setLastObstaclePosition(GameStrategyContext* gameStrategyContext) {
    Point* robotPosition = gameStrategyContext->robotPosition;
    Point* lastObstaclePosition = gameStrategyContext->lastObstaclePosition;
    float angleRadian = gameStrategyContext->robotAngleRadian;
    computeDirectionPoint(robotPosition, lastObstaclePosition, DISTANCE_OBSTACLE, angleRadian);
}

void handleCollision(GameStrategyContext* gameStrategyContext) {
    // OutputStream* logStream = getDebugOutputStreamLogger();
    /*
    Timer* strategyTimer = gameStrategyContext->strategyTimer;
    // Mark the timer.
    if (strategyTimer != NULL) {
        gameStrategyContext->timeSinceLastCollision = (float) strategyTimer->time;
    }
    #ifdef DEBUG_STRATEGY_HANDLER
        appendStringAndDecf(logStream, "\nCollision at time:", gameStrategyContext->timeSinceLastCollision);
        appendString(logStream "\nhandleCollision");
    #endif

    // Clears the current path and actions
    clearCurrentTarget(gameStrategyContext);

    setLastObstaclePosition(gameStrategyContext);
    updatePathsAvailability(gameStrategyContext);
    */
}


