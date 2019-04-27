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
    // 20 Samples = 0.05f for Step
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
    bool computePath = mustComputePaths(gameStrategyContext);
    Navigation* navigation = gameStrategyContext->navigation;
    PathList* paths = getNavigationPathList(navigation);
    unsigned int i;
    BSplineCurve curve;
    for (i = 0; i < paths->size; i++) {
        PathData* pathData = getPath(paths, i);
        if (computePath) {
            isPathAvailable(gameStrategyContext, pathData, &curve);
        }
    }
}


