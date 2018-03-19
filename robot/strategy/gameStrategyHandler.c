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

#include "../../drivers/motion/motionDriver.h"

#include "../../motion/extended/bspline.h"
#include "../../motion/extended/bsplineList.h"

#include "../../navigation/location.h"
#include "../../navigation/locationList.h"
#include "../../navigation/navigation.h"
#include "../../navigation/path.h"
#include "../../navigation/pathList.h"

#include "../../drivers/motion/extendedMotionDriver.h"
#include "../../drivers/motion/motionDriver.h"

#include "../../robot/strategy/gameTargetList.h"
#include "../../robot/2012/strategy2012Utils.h"

// Strategy Context
static GameStrategyContext strategyContext;

// Strategy timer
static Timer* strategyTimer;

/** The index of the timer (used to manage path availability). */
#define STRATEGY_TIMER_INDEX 18

GameStrategyContext* getStrategyContext() {
    return &strategyContext;
}

#define ANGLE_180 1800
#define ANGLE_360 3600

void strategyTimerCallback(Timer* timer) {
    if (strategyTimer->time > strategyContext.timeSinceLastCollision + RESET_OBSTACLE_COLLISION_TIME_SECOND) {
        #ifdef DEBUG_OPPONENT_ROBOT
            OutputStream* logStream = getInfoOutputStreamLogger();
            appendString(logStream, "resetAllPathsAsAvailable\n");
        #endif
        resetAllPathsAsAvailable();
        // remove the last Obstacle position
        strategyContext.lastObstaclePosition.x = 0;
        strategyContext.lastObstaclePosition.y = 0;
    }
}

void initStrategyHandler() {
    // strategyTimer = addTimer(STRATEGY_TIMER_INDEX, TIME_DIVIDER_1_HERTZ, &strategyTimerCallback, "GAME_STRATEGY");
}

/**
 * Clears the current path and actions.
 * Useful when we want to cancel a target or go out from a target.
 */
void clearCurrentTarget() {
    clearLocationList(&(strategyContext.currentTrajectory));
    strategyContext.currentTarget = NULL;
    strategyContext.currentTargetAction = NULL;
}

/**
 * @private
 */
void findNextTarget() {
    appendString(getDebugOutputStreamLogger(), "findNextTarget\n");

    unsigned int targetHandledCount = getTargetHandledCount();
    if (targetHandledCount >= strategyContext.maxTargetToHandle) {
        clearCurrentTarget();
        appendStringAndDec(getDebugOutputStreamLogger(), "Reach Max Target To Handle:", targetHandledCount);
        println(getDebugOutputStreamLogger());
        return;
    }

    // global points
    LocationList* navigationLocationList = getNavigationLocationList();

    Point* robotPosition = &(strategyContext.robotPosition);
    // Find nearest location
    strategyContext.nearestLocation = getNearestLocation(navigationLocationList, robotPosition->x, robotPosition->y);

    #ifdef DEBUG_STRATEGY_HANDLER
        appendString(getDebugOutputStreamLogger(), "\tNearest Location:");    
        printLocation(getDebugOutputStreamLogger(), strategyContext.nearestLocation);
        appendString(getDebugOutputStreamLogger(), "\tcomputeBestNextTargetAction:\n");    
    #endif

    // Find best Target, store LocationList in the context in currentTrajectory
    computeBestNextTarget(&strategyContext);

    #ifdef DEBUG_STRATEGY_HANDLER
        appendString(getDebugOutputStreamLogger(), "\t\tbestTarget:");
        if (strategyContext.currentTarget != NULL) {
            printGameTarget(getDebugOutputStreamLogger(), strategyContext.currentTarget, false);
        }
        else {
            appendString(getDebugOutputStreamLogger(), "NULL\n");
        }
        appendString(getDebugOutputStreamLogger(), "\t\tbestTargetAction:");
        if (strategyContext.currentTargetAction != NULL) {
            printGameTargetAction(getDebugOutputStreamLogger(), strategyContext.currentTargetAction, false);
        }
        else {
            appendString(getDebugOutputStreamLogger(), "NULL\n");
        }
    #endif
}

void markTargetAsHandled() {
    // mark the target as unavailable
    strategyContext.currentTarget->status = TARGET_HANDLED;
    // reset current Target
    strategyContext.currentTarget = NULL;
    strategyContext.currentTargetAction = NULL;
    incTargetHandledCount();
}

void markTargetInUse() {
    // mark the target as being used
    strategyContext.currentTarget->status = TARGET_INUSE;
}

/**
 * Execute the target actions, and return true if there is a an action called, false else
 * @private
 */
bool executeTargetActions() {
    #ifdef DEBUG_STRATEGY_HANDLER
        appendString(getDebugOutputStreamLogger(), "executeTargetActions\n");
    #endif

    markTargetInUse();

    GameTargetAction* targetAction = strategyContext.currentTargetAction;
    GameTargetActionItemList* actionItemList = targetAction->actionItemList;
    if (actionItemList == NULL) {
        #ifdef DEBUG_STRATEGY_HANDLER
            appendString(getDebugOutputStreamLogger(), "-> no actions for this target\n");
        #endif
        markTargetAsHandled();
        return false;
    }

    // There is actionItem in progress
    if (actionItemList != NULL && targetActionItemListHasNext(actionItemList)) {
        GameTargetActionItem* actionItem = targetActionItemListNext(actionItemList);

        #ifdef DEBUG_STRATEGY_HANDLER
            printGameTargetActionItem(getDebugOutputStreamLogger(), actionItem);
        #endif

        // Do the action item
        actionItem->actionItemFunction();
        return true;
    }
    else {
        markTargetAsHandled();
        // we do nothing
        return false;
    }
    return true;
}

void motionGoLocation(Location* location, 
                    float angle,
                    float controlPointDistance1, float controlPointDistance2,
                    float accelerationFactor, float speedFactor ) {

    #ifdef DEBUG_STRATEGY_HANDLER
        appendString(getDebugOutputStreamLogger(), "motionGoLocation:goto:");    
        printLocation(getDebugOutputStreamLogger(), location);
    #endif

    angle = changeAngleForColor(angle);
    motionDriverBSplineAbsolute(location->x, location->y,
                                angle,
                                controlPointDistance1, controlPointDistance2,
                                accelerationFactor, speedFactor);

    // Simulate as if the robot goes to the position with a small error
    #ifdef SIMULATE_ROBOT
        strategyContext.robotPosition.x = location->x + 1;
        strategyContext.robotPosition.y = location->y + 1;
    #endif
}

float mod360(float value) {
    if (value < - ANGLE_180) {
        return (value + ANGLE_360);
    } else if (value >= ANGLE_180) {
        return (value - ANGLE_360);
    }
    return value;
}

void rotateAbsolute(float angle) {
    angle = changeAngleForColor(angle);
    GameStrategyContext* strategyContext = getStrategyContext();
    float robotAngle = strategyContext->robotAngle;
    float diff = mod360(angle - robotAngle);
    /*
    if (abs(diff) < ANGLE_ROTATION_MIN) {
        return;
    }
    */

    #ifdef DEBUG_STRATEGY_HANDLER
        appendStringAndDecf(getDebugOutputStreamLogger(), "rotateAbsolute:angle:", diff);    
        appendString(getDebugOutputStreamLogger(), " deg\n");
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
}

bool motionRotateToFollowPath(PathData* pathData, bool reversed) {
    float angle;
    if (reversed) {
        if (pathData->mustGoBackward) {
            angle = getAngle2Path(pathData);
        } else {
            angle = mod360(ANGLE_180 + getAngle2Path(pathData));
        }
    } else {
        angle = getAngle1Path(pathData);
    }

    float diff = mod360(angle - strategyContext.robotAngle);
    if (fabs(diff) < ANGLE_ROTATION_MIN) {
        return false;
    }

    #ifdef DEBUG_STRATEGY_HANDLER
        appendStringAndDecf(getDebugOutputStreamLogger(), "motionRotateToFollowPath:angle:", diff);    
        appendString(getDebugOutputStreamLogger(), " degree\n");
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

    return true;
}

void motionFollowPath(PathData* pathData, bool reversed) {
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
            angle = mod360(ANGLE_180 + getAngle1Path(pathData));
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
        appendString(getDebugOutputStreamLogger(), "motionFollowPath:goto:");    
        printLocation(getDebugOutputStreamLogger(), location);
    #endif

    // cast to unsigned, negative signed char send 00
    motionDriverBSplineAbsolute(location->x, location->y, angle, cp1, cp2,
        pathData->accelerationFactor, pathData->speedFactor);

    // Simulate as if the robot goes to the position with a small error
    #ifdef SIMULATE_ROBOT
        strategyContext.robotPosition.x = location->x + 1;
        strategyContext.robotPosition.y = location->y + 1;
        strategyContext.robotAngle = angle;
    #endif
}

/**
* Handle the trajectory and return true if we go to a location, false else.
* @private
*/
bool handleCurrentTrajectory() {
    #ifdef DEBUG_STRATEGY_HANDLER
        appendString(getDebugOutputStreamLogger(), "handleCurrentTrajectory\n");    
    #endif

    LocationList* currentTrajectory = &(strategyContext.currentTrajectory);

    #ifdef DEBUG_STRATEGY_HANDLER
        // printLocationList(getDebugOutputStreamLogger(), "currentTrajectory:", currentTrajectory);    
    #endif

    if (currentTrajectory == NULL || currentTrajectory->size < 2) {
        #ifdef DEBUG_STRATEGY_HANDLER
            appendString(getDebugOutputStreamLogger(), "no more locations to reach\n");    
        #endif

        // no more locations to reach
        clearLocationList(currentTrajectory);
        return false;
    }

    Location* start = getLocation(currentTrajectory, 0);
    Location* end = getLocation(currentTrajectory, 1);
    bool reversed;
    PathData* pathData = getPathOfLocations(getNavigationPathList(), start, end, &reversed);

    // Follows the path
    if (!motionRotateToFollowPath(pathData, reversed)) {
        motionFollowPath(pathData, reversed);
        removeFirstLocation(currentTrajectory);
    }
    return true;
}

void computePoint(Point* ref, Point* cp, float distance, float angle) {
    float a = degToRad(angle);
    float dca = cosf(a) * distance;
    float dsa = sinf(a) * distance;
    cp->x = ref->x + dca;
    cp->y = ref->y + dsa;
}

bool isColliding(Point* path, Point* obstacle) {
    float d = distanceBetweenPoints(path, obstacle);
    bool result = (d < DISTANCE_OPPONENT_TO_PATH);
    return result;
}

bool isValidLocation(Point* p) {
    return (p->x !=0) && (p->y != 0);
}

/**
 * Control point distance to mm.
 */
float cpToDistance(float distance) {
    return (distance * 10.0f);
}

/**
 * Loop on a pathData, to know if the path has an intersection with the opponentRobotPosition.
 * @private
 */
bool isPathAvailable(PathData* pathData, BSplineCurve* curve) {
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
    Point* opponentRobotPosition = &(strategyContext.opponentRobotPosition);
    Point* lastObstaclePosition = &(strategyContext.lastObstaclePosition);
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
}

bool mustComputePaths() {
    Point* opponentRobotPosition = &(strategyContext.opponentRobotPosition);
    Point* lastObstaclePosition = &(strategyContext.lastObstaclePosition);
    bool opponentPresent = isValidLocation(opponentRobotPosition);
    bool obstaclePresent = isValidLocation(lastObstaclePosition);

    return opponentPresent || obstaclePresent;

    // TODO
    // Case when the robot position is detected himself as the opponent robot !!!
    // All paths will be marked as unavailable, but the robot will try the path even (cost is only more huge)
}

void updatePathsAvailability() {
    #ifdef DEBUG_OPPONENT_ROBOT
        OutputStream* logStream = getInfoOutputStreamLogger();
        appendString(logStream, "\nUpdating available paths");
    //    printGameStrategyContext(logStream, getStrategyContext());
    #endif

    bool computePath = mustComputePaths();
    if (!computePath) {
        appendString(logStream, "\nDon't compute Path !");
    }    
    PathList* paths = getNavigationPathList();
    unsigned int i;
    for (i = 0; i < paths->size; i++) {
        PathData* pathData = getPath(paths, i);
        // by default, path is available
        bool available = true;
        // Don't do the compute if it's not necessary
        if (computePath) {    
            available = isPathAvailable(pathData, NULL);
        }
        setPathAvailability(i, available);
    }

    #ifdef DEBUG_OPPONENT_ROBOT
        // LOG
        unsigned int k;
        for (k = 0; k < paths->size; k++) {
            PathData* pathData = getPath(paths, k);
            if (!getPathAvailability(k)) {
                appendString(logStream, "\n");
                appendString(logStream, pathData->location1->name);
                appendString(logStream, "->");
                appendString(logStream, pathData->location2->name);
                appendString(logStream, ": UNAVAILABLE");        
            }
        }
        appendString(logStream, "\n");
    #endif
}

void setLastObstaclePosition() {
    Point* robotPosition = &(strategyContext.robotPosition);
    Point* lastObstaclePosition = &(strategyContext.lastObstaclePosition);
    float angle = strategyContext.robotAngle;
    computePoint(robotPosition, lastObstaclePosition, DISTANCE_OBSTACLE, angle);
}

void handleCollision() {
    // Mark the timer.
    if (strategyTimer != NULL) {
        strategyContext.timeSinceLastCollision = (float) strategyTimer->time;
    }
    #ifdef DEBUG_STRATEGY_HANDLER
        appendStringAndDecf(getDebugOutputStreamLogger(), "\nCollision at time:", strategyContext.timeSinceLastCollision);    
        appendString(getDebugOutputStreamLogger(), "\nhandleCollision");    
    #endif
    
    // Clears the current path and actions
    clearCurrentTarget();

    setLastObstaclePosition();
    updatePathsAvailability();
}

bool nextStep() {
    unsigned int counter = 0;
    #ifdef DEBUG_STRATEGY_HANDLER
        appendString(getDebugOutputStreamLogger(), "nextStep\n");    
    #endif
    while (1) {
        counter++;
        #ifdef DEBUG_STRATEGY_HANDLER
            appendStringAndDec(getDebugOutputStreamLogger(), "nextStep=>", counter);    
            println(getDebugOutputStreamLogger());
        #endif
        GameTargetAction* targetAction = strategyContext.currentTargetAction;
    
        if (getLocationCount(&(strategyContext.currentTrajectory)) != 0) {
            if (!handleCurrentTrajectory()) {
                continue;
            }
            return true;
        }
        else if (targetAction != NULL) {
            if (!executeTargetActions()) {
                // we will return on a different condition.
                continue;
            }
            return true;
        }
        else if (targetAction == NULL) {
            // no target, search a new one
            findNextTarget();
            if (strategyContext.currentTarget == NULL) {
                #ifdef DEBUG_STRATEGY_HANDLER
                    appendString(getDebugOutputStreamLogger(), "no more targets -> stopping");
                #endif
                clearCurrentTarget();
                return false;
            }
            // Next target created a new current trajectory
            if (getLocationCount(&(strategyContext.currentTrajectory)) != 0) {
                if (!handleCurrentTrajectory()) {
                    continue;
                }
                return true;
            }
        } else {
            if (!executeTargetActions()) {
                // we will return on a different condition.
                continue;
            }
            return true;
        }
    }
    return true;
}


