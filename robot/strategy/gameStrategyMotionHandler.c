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

// COMBINAISON OF FOLLOW / ROTATE

bool followComputedNextPath(GameStrategyContext* gameStrategyContext) {
    Navigation* navigation = gameStrategyContext->navigation;
    // navigation->path
    Location* startLocation = gameStrategyContext->nearestLocation;
    if (startLocation == NULL) {
        writeError(LOCATION_START_NULL);
        return false;
    }
    Location* endLocation = startLocation->computedNextLocation;
    if (endLocation == NULL) {
        // writeError(LOCATION_END_NULL); // No need to throw an exception
        return false;
    }
    PathList* pathList = getNavigationPathList(navigation);
    PathData* pathData = getPathOfLocations(pathList, startLocation, endLocation);
    // Check if to follow the path, we need to do first a rotation (to avoid problem on bSpline)
    if (!motionRotateToFollowPath(gameStrategyContext, pathData)) {
        // If this is not the case, we ask to follow the path
        return motionFollowPath(gameStrategyContext, pathData);
    }
    return true;
}
