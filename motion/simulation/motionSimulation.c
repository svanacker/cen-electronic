#include "motionSimulation.h"
#include <math.h>
#include <stdlib.h>

#include "../../robot/strategy/gameStrategyContext.h"

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

#include "../../motion/extended/bspline.h"
#include "../../motion/extended/bsplineMotion.h"

static BSplineCurve bSplineCurveSimulation;
static Point lastRobotPosition;
static bool simulateFlag;
static float bSplineTime;
static float bSplineIncrement;

/**
 * @private / Callback
 */
void interruptMotionSimulationCallbackFunc(Timer* timer) {
    if (timer == NULL) {
        writeError(TIMER_NULL);
        return;
    }
    GameStrategyContext* gameStrategyContext = (GameStrategyContext*) timer->object;
    if (gameStrategyContext == NULL) {
        writeError(TIMER_OBJECT_NULL);
        return;
    }

    if (!simulateFlag) {
        return;
    }

    Point* robotPosition = gameStrategyContext->robotPosition;

    // BSpline Follow
    bSplineTime += bSplineIncrement;
    if (bSplineTime > 1.0f) {
        bSplineTime = 1.0f + (rand() % 100) * 0.0002f - 0.01f;
        simulateFlag = false;
        updateStrategyContextTrajectoryType(gameStrategyContext, TRAJECTORY_TYPE_NONE);
    }
    // In Every case, Move the robot by passing the robotPosition point ...
    Point computedPoint;
    computeBSplinePoint(&bSplineCurveSimulation, bSplineTime, &computedPoint);
    robotPosition->x = lastRobotPosition.x + computedPoint.x;
    robotPosition->y = lastRobotPosition.y + computedPoint.y;

    gameStrategyContext->robotAngleRadian = computeBSplineOrientationWithDerivative(&bSplineCurveSimulation, bSplineTime);

    // Rotation

}

void initMotionSimulation(GameStrategyContext* gameStrategyContext) {
    Timer* timer = addTimer(TIMER_MOTION_SIMULATION_PC,
            TIME_DIVIDER_5_HERTZ,
            &interruptMotionSimulationCallbackFunc,
            "MOTION_SIMUL_PC",
            (int*) gameStrategyContext);
    timer->enabled = true;
}

// --------------------------------

void simulateBSplineAbsolute(GameStrategyContext* gameStrategyContext, float destX, float destY, float angleRadian, float dist0, float dist1, float accelerationFactor, float speedFactor) {
    lastRobotPosition.x = gameStrategyContext->robotPosition->x;
    lastRobotPosition.y = gameStrategyContext->robotPosition->y;

    updateSimpleSplineWithDistance(&bSplineCurveSimulation,
            destX - lastRobotPosition.x, destY - lastRobotPosition.y,
            angleRadian,
            dist0, dist1,
            accelerationFactor, speedFactor,
            false);

    float distance = computeBSplineArcLength(&bSplineCurveSimulation, 0.01f);
    bSplineTime = 0.0f;
    // we consider that we could do a distance of 250 mm / s
    // At 5Hz, we must increment by 
    bSplineIncrement = 250.0f / distance / 5.0f;
    if (dist0 > 0.0f) {
        updateStrategyContextTrajectoryType(gameStrategyContext, TRAJECTORY_TYPE_FORWARD);
    } else {
        updateStrategyContextTrajectoryType(gameStrategyContext, TRAJECTORY_TYPE_BACKWARD);
    }
    simulateFlag = true;
}

void simulateMotionCancel(GameStrategyContext* gameStrategyContext) {
    simulateFlag = false;
}

static MotionSimulationParameter motionSimulationParameter;

MotionSimulationParameter* getMotionSimulationParameter() {
    return &motionSimulationParameter;
}

