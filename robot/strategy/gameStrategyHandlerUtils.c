#include "gameStrategyHandlerUtils.h"

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

#include "../../client/motion/extended/clientExtendedMotion.h"
#include "../../client/motion/simple/clientMotion.h"
#include "../../client/motion/position/clientTrajectory.h"

#include "../../robot/strategy/gameTargetList.h"
#include "../../robot/2018/strategy2018Utils.h"
#include "../../robot/robot.h"

bool updateMotorBoardRobotPosition(GameStrategyContext* gameStrategyContext) {
    Point* robotPosition = gameStrategyContext->robotPosition;
    return clientTrajectorySetAbsolutePosition(robotPosition->x, robotPosition->y, gameStrategyContext->robotAngleRadian);
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
    gameStrategyContext->currentTargetAction = NULL;
}

void markTargetAsHandled(GameStrategyContext* gameStrategyContext) {
    GameTarget* currentTarget = gameStrategyContext->currentTarget;
    if (currentTarget == NULL) {
        return;
    }
    // mark the target as unavailable
    currentTarget->status = TARGET_HANDLED;
    // reset current Target
    currentTarget = NULL;
    gameStrategyContext->currentTargetAction = NULL;
    incTargetHandledCount();
}

void markTargetInUse(GameStrategyContext* gameStrategyContext) {
    GameTarget* currentTarget = gameStrategyContext->currentTarget;
    if (currentTarget == NULL) {
        return;
    }
    // mark the target as being used
    currentTarget->status = TARGET_INUSE;
}

void motionGoLocation(Location* location,
    float angle,
    float controlPointDistance1, float controlPointDistance2,
    float accelerationFactor, float speedFactor) {
    /*
    angle = changeAngleForColor(angle);
    clientExtendedMotionBSplineAbsolute(location->x, location->y,
                                angle,
                                controlPointDistance1, controlPointDistance2,
                                accelerationFactor, speedFactor);

    // Simulate as if the robot goes to the position with a small error
    #ifdef SIMULATE_ROBOT
        strategyContext.robotPosition.x = location->x + 1;
        strategyContext.robotPosition.y = location->y + 1;
    #endif
    */
}

/*
float mod360(float value) {
    if (value < - ANGLE_DECI_DEG_180) {
        return (value + ANGLE_360);
    } else if (value >= ANGLE_DECI_DEG_180) {
        return (value - ANGLE_360);
    }
    return value;
}
*/

void rotateAbsolute(GameStrategyContext* gameStrategyContext, float angle) {
    // OutputStream* logStream = getDebugOutputStreamLogger();
    /* TODO
    angle = changeAngleForColor(angle);
    float robotAngle = gameStrategyContext->robotAngleRadian;
    float diff = mod360(angle - robotAngle);
    if (abs(diff) < ANGLE_ROTATION_MIN) {
        return;
    }

    #ifdef DEBUG_STRATEGY_HANDLER
        appendStringAndDecf(logStream, "rotateAbsolute:angle:", diff);
        appendString(logStream, " deg\n");
    #endif
    if (diff == 0) {
        // instruction with 0 does not notify position.
        diff = 1;
    }
    if (diff > 0) {
        motionDriverLeft(diff);
    } else {
        motionDriverRight(-diff);
    }

    // Simulate as if the robot goes to the position with a small error
    #ifdef SIMULATE_ROBOT
        strategyContext->robotAngle += diff;
    #endif
    */
}

bool motionRotateToFollowPath(GameStrategyContext* gmeStrategyContext, PathData* pathData, bool reversed) {
    /*
    float angle;
    if (reversed) {
        if (pathData->mustGoBackward) {
            angle = getAngle2Path(pathData);
        } else {
            angle = mod360(ANGLE_DECI_DEG_180 + getAngle2Path(pathData));
        }
    } else {
        angle = getAngle1Path(pathData);
    }

    float diff = mod360(angle - gmeStrategyContext->robotAngle);
    if (fabs(diff) < ANGLE_ROTATION_MIN) {
        return false;
    }

    #ifdef DEBUG_STRATEGY_HANDLER
        appendStringAndDecf(logStream, "motionRotateToFollowPath:angle:", diff);
        appendString(logStream, " degree\n");
    #endif

    if (diff > 0) {
        motionDriverLeft((float) diff);
    } else {
        motionDriverRight((float)-diff);
    }

    // Simulate as if the robot goes to the position with a small error
    #ifdef SIMULATE_ROBOT
        strategyContext.robotAngle += diff;
    #endif

    */

    return true;
}

void motionFollowPath(GameStrategyContext* gmeStrategyContext, PathData* pathData, bool reversed) {
    /*
    Location* location;
    float angle;
    float cp1;
    float cp2;
    if (reversed) {
        location = pathData->location1;
        if (pathData->mustGoBackward) {
            // reverse the trajectory by going backward
            angle = getAngle1Path(pathData);
            cp1 = -pathData->controlPointDistance2;
            cp2 = -pathData->controlPointDistance1;
        } else {
            // reverse the trajectory symmetrically
            angle = mod360(ANGLE_DECI_DEG_180 + getAngle1Path(pathData));
            cp1 = pathData->controlPointDistance2;
            cp2 = pathData->controlPointDistance1;
        }
    } else {
        location = pathData->location2;
        angle = getAngle2Path(pathData);
        cp1 = pathData->controlPointDistance1;
        cp2 = pathData->controlPointDistance2;
    }

    #ifdef DEBUG_STRATEGY_HANDLER
        appendString(logStream, "motionFollowPath:goto:");
        printLocation(logStream, location);
    #endif

    // cast to unsigned, negative signed char send 00
    clientExtendedMotionBSplineAbsolute(location->x, location->y, angle, cp1, cp2,
        pathData->accelerationFactor, pathData->speedFactor);

    // Simulate as if the robot goes to the position with a small error
    #ifdef SIMULATE_ROBOT
        strategyContext.robotPosition.x = location->x + 1;
        strategyContext.robotPosition.y = location->y + 1;
        strategyContext.robotAngle = angle;
    #endif
    */
}

bool isColliding(Point* path, Point* obstacle) {
    float d = distanceBetweenPoints(path, obstacle);
    bool result = (d < DISTANCE_OPPONENT_TO_PATH);
    return result;
}

bool isValidLocation(Point* p) {
    // TODO : To Check
    return (p->x != 0) && (p->y != 0);
}

/**
 * Loop on a pathData, to know if the path has an intersection with the opponentRobotPosition.
 * @private
 */
bool isPathAvailable(GameStrategyContext* gameStrategyContext, PathData* pathData, BSplineCurve* curve) {
    /*
    // TODO : Fix why curve must be handled
    if (curve == NULL) {
        return true;
    }
    Point* p0 = &(curve->p0);
    p0->x = (float) pathData->location1->x;
    p0->y = (float) pathData->location1->y;
    Point* p3 = &(curve->p3);
    p3->x = (float) pathData->location2->x;
    p3->y = (float) pathData->location2->y;
    float angle1 = getAngle1Path(pathData);
    float angle2 = getAngle2Path(pathData);
    float d1 = cpToDistance(pathData->controlPointDistance1);
    float d2 = cpToDistance(-pathData->controlPointDistance2);
    computePoint(p0, &(curve->p1), d1, angle1);
    computePoint(p3, &(curve->p2), d2, angle2);

    int i;
    Point p;
    Point* opponentRobotPosition = gameStrategyContext->opponentRobotPosition;
    Point* lastObstaclePosition = gameStrategyContext->lastObstaclePosition;
    bool opponentPresent = isValidLocation(opponentRobotPosition);
    bool obstaclePresent = isValidLocation(lastObstaclePosition);
    for (i = 0; i < 10; i++) {
        computeBSplinePoint(curve, 0.1f * i, &p);
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
    */
    return false;
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


