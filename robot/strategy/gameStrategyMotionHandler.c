#include "gameStrategyMotionHandler.h"

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
}

bool motionRotateToFollowPath(GameStrategyContext* gameStrategyContext, PathData* pathData) {
    float angle = getPathStartAngleRadian(pathData);

    float diff = mod2PI(angle - gameStrategyContext->robotAngleRadian);
    if (fabs(diff) < ANGLE_ROTATION_MIN) {
        return false;
    }

    if (diff > 0.0f) {
        motionDriverLeft((float) diff);
    } else {
        motionDriverRight((float)-diff);
    }

    // Simulate as if the robot goes to the position with a small error to be sure
    // that we do not rely the navigation on just exact computation
    if (gameStrategyContext->simulateMove) {
        gameStrategyContext->robotAngleRadian += diff + 0.001f;
    }

    return true;
}

void motionFollowPath(GameStrategyContext* gameStrategyContext, PathData* pathData) {
    Location* location = pathData->location2;

    float angle = getPathEndAngleRadian(pathData);
    float cp1 = pathData->controlPointDistance1;
    float cp2 = pathData->controlPointDistance2;

    clientExtendedMotionBSplineAbsolute(location->x, location->y, angle, cp1, cp2,
        pathData->accelerationFactor, pathData->speedFactor);

    // Simulate as if the robot goes to the position with a small error to be sure that 
    // algorithm to find nearest position are ok
    if (gameStrategyContext->simulateMove) {
        gameStrategyContext->robotPosition->x = location->x + 1.0f;
        gameStrategyContext->robotPosition->y = location->y + 1.0f;
        gameStrategyContext->robotAngleRadian = angle;
    }
}
