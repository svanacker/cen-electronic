#ifndef TOF_DETECTION_UTILS_H
#define TOF_DETECTION_UTILS_H

#include <stdbool.h>

#include "../../common/2d/2d.h"
#include "tof.h"

/**
 * Returns if the tof distance in the Threshold Range (which means that we detects
 * something)
 * @param tofSensor
 * @return true if distance > 0 & in [distanceMinThreshold .. distanceMaxThreshold]
 */
bool isTofDistanceInRange(TofSensor* tofSensor);

/**
 * We compute the real point of the tofSensor by taking into account
 * - The point of view (robotCentralPoint) and his orientation
 * - The position (polar coordinates) of the tofSensor
 * - The distance to the center of the Robot
 */
void tofComputeTofPointOfView(TofSensor* tofSensor, Point* robotCentralPoint, float robotOrientation, Point* resultPoint);

void tofComputePoint(TofSensor* tofSensor,
    Point* tofPointOfView,
    float pointOfViewAngleRadian,
    float distance,
    float coneAngle,
    Point* resultPoint);

/**
 * Compute if a something is detected from the pointOfView (Robot->position and robot->angle) and if something is detected,
 * them the point given in parameter will be updated.
 * @return true if a something was detected
 */
bool tofComputeDetectedPointIfAny(TofSensor* tofSensor, Point* pointOfView, float pointOfViewAngleRadian, Point* pointToUpdateIfAny);

/**
 * Is the tof sensor backward oriented, and in this case, we don't check them
 * when we go forward 
 */
bool isTofSensorBackwardOriented(TofSensor* tofSensor);

#endif