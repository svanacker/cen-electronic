#include "tofDetectionUtils.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../../common/2d/2d.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"

#include "../../common/math/cenMath.h"

bool isTofDistanceInRange(TofSensor* tofSensor) {
    unsigned int distance = tofSensor->lastDistanceMM;

    // distance != 0 (means tof problem while measuring)
    // distance <= threshold
    return (distance != 0
            && tofSensor->thresholdMinDistanceMM < distance
            && distance < tofSensor->thresholdMaxDistanceMM);
}

/**
 * We compute the real point of the tofSensor by taking into account
 * - The position (polar coordinates) of the tofSensor
 * - The distance to the center of the Robot
 */
void tofComputeTofPointOfView(TofSensor* tofSensor, Point* robotCentralPoint, float robotOrientation, Point* resultPoint) {
    // We compute the real point of the tofSensor by taking into account
    // - The position (polar coordinates) of the tofSensor
    // - The distance to the center of the Robot
    computeDirectionPoint(robotCentralPoint,
            resultPoint,
            tofSensor->distanceFromRobotCenter,
            robotOrientation +
            tofSensor->angleFromRobotCenterRadian
            );
}

void tofComputePoint(TofSensor* tofSensor,
        Point* tofPointOfView,
        float pointOfViewAngleRadian,
        float distance,
        float coneAngle,
        Point* resultPoint) {
    // we compute the projection of the point along the point of view angle
    // But from the point of view of the tofSensor
    computeDirectionPoint(tofPointOfView,
            resultPoint,
            (float) distance,
            pointOfViewAngleRadian
            + tofSensor->orientationRadian
            + coneAngle);

}

bool tofComputeDetectedPointIfAny(TofSensor* tofSensor, Point* pointOfView, float pointOfViewAngleRadian, Point* pointToUpdateIfAny) {
    unsigned int distance = tofSensor->lastDistanceMM;
    // If No Point of View (Robot Position) is provided
    if (pointOfView == NULL) {
        return false;
    }
    if (!isTofDistanceInRange(tofSensor)) {
        // we do not provide any point
        return false;
    }

    // We compute the real point of the tofSensor by taking into account
    // - The position (polar coordinates) of the tofSensor
    // - The distance to the center of the Robot
    Point tofPointOfView;
    tofComputeTofPointOfView(tofSensor, pointOfView, pointOfViewAngleRadian, &tofPointOfView);

    // we compute the projection of the point along the point of view angle
    // But from the point of view of the tofSensor
    tofComputePoint(tofSensor,
            &tofPointOfView,
            pointOfViewAngleRadian + tofSensor->orientationRadian,
            (float) distance,
            // We could not know the real angle of the tof in VL530X
            // In that case, we consider that the point is forward and has no coneAngle (0° and not between -15° and +15°)
            0.0f,
            pointToUpdateIfAny);

    return true;
}

bool isTofSensorBackwardOriented(TofSensor* tofSensor) {
    return (tofSensor->orientationRadian > (PI / 2.0f) ||
            tofSensor->orientationRadian < (-PI / 2.0f));
}