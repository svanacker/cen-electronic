#include "tofPc.h"

#include "../tof.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../../../common/2d/2d.h"

#include "../../../common/log/logger.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

#include "../../../common/math/cenmath.h"

#include "../../../drivers/tof/tofDetectionUtils.h"

#include "../../../robot/fake/fakeRobot.h"

#include "../../../robot/strategy/gameStrategyContext.h"

bool tofSensorStartPc(TofSensor* tofSensor, bool restart, bool debug) {
    if (restart) {
        appendStringLN(getDebugOutputStreamLogger(), "TOF SENSOR RESTART");
    } else {
        tofSensor->startResult = TOF_SENSOR_START_RESULT_OK;
    }
    return true;
}

/**
 *
 */
GameStrategyContext* getTofSensorGameStrategyContext(TofSensor* tofSensor) {
    return (GameStrategyContext*) tofSensor->object;
}

/**
 * Tof POO Implementation for PC
 * @private
 */
unsigned int tofSensorGetDistanceMMPc(TofSensor* tofSensor) {
    if (!tofSensor->enabled) {
        return 0;
    }
    FakeRobot* fakeRobot = getFakeRobotInstance();

    GameStrategyContext* gameStrategyContext = getTofSensorGameStrategyContext(tofSensor);

    Point* robotPosition = gameStrategyContext->robotPosition;
    float robotAngle = gameStrategyContext->robotAngleRadian;

    // Algorithm like "Ray Tracing"
    float distance;
    Point resultPoint;
    tofSensor->lastDistanceMM = 8192;
    float coneAngle = 0.0f;

    for (distance = 0.0f; distance < 8192.0f; distance += 5.0f) {
        bool found = false;
        // To simulate the "coneAngle" of the tof !
        for (coneAngle = -tofSensor->beamAngleRadian / 2.0f; coneAngle < tofSensor->beamAngleRadian / 2.0f; coneAngle += tofSensor->beamAngleRadian / 20.0f) {
            tofComputePoint(tofSensor, robotPosition, robotAngle, distance, coneAngle, &resultPoint);
            // If we detect the fakeRobot
            if (isInCircle2(fakeRobot->x, fakeRobot->y, fakeRobot->radius, resultPoint.x, resultPoint.y)) {
                tofSensor->lastDistanceMM = (unsigned int) distance;
                found = true;
                break;
            }
        }
        if (found) {
            break;
        }
    }
    return tofSensor->lastDistanceMM;
}

void initTofSensorPc(TofSensor* tofSensor, int* object) {
    tofSensor->type = TOF_SENSOR_TYPE_PC;
    tofSensor->beamAngleRadian = degToRad(TOF_PC_BEAM_ANGLE_DEGREE);
    initTofSensor(tofSensor,
            &tofSensorStartPc,
            &tofSensorGetDistanceMMPc,
            object);
}
