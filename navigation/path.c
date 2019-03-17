#include <stdlib.h>

#include "path.h"
#include "location.h"

#include "../common/commons.h"

#include "../common/2d/2d.h"

#include "../common/error/error.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

#include "../client/motion/extended/clientExtendedMotion.h"


/*
float getAngle1Path(PathData* pathData) {
    float angle1 = pathData->angle1;
    float result = changeAngleForColor(angle1);
    return result;
}

float getAngle2Path(PathData* pathData) {
    float angle2 = pathData->angle2;
    float result = changeAngleForColor(angle2);
    return result;
}
*/

void initPathData(PathData* pathData, 
                    Location* location1,
                     Location* location2, 
                     float cost,
                     float controlPointDistance1,
                     float controlPointDistance2,
                     float angleRadian1,
                     float angleRadian2,
                     float accelerationFactor,
                     float speedFactor) {
    if (pathData == NULL) {
        writeError(PATH_NULL);
        return;
    }
    if (location1 == NULL || location2 == NULL) {
        writeError(LOCATION_NULL);
        return;
    }
    pathData->location1 = location1;
    pathData->location2 = location2;
    pathData->controlPointDistance1 = controlPointDistance1;
    pathData->controlPointDistance2 = controlPointDistance2;
    pathData->angleRadian1 = angleRadian1;
    pathData->angleRadian2 = angleRadian2;
    pathData->cost = cost;
    pathData->accelerationFactor = accelerationFactor;
    pathData->speedFactor = speedFactor;
    pathData->mustGoBackward = controlPointDistance1 < 0;
}

void initAsymmetricPathData(
                      PathData* pathData,
                     Location* location1,
                     Location* location2, 
                     float cost,
                     float controlPointDistance1,
                     float controlPointDistance2,
                     float angle1,
                     float angle2,
                     unsigned char accelerationFactor,
                     unsigned char speedFactor) {
    initPathData(pathData, location1, location2, cost, controlPointDistance1, controlPointDistance2, angle1, angle2, accelerationFactor, speedFactor);
    pathData->mustGoBackward = controlPointDistance1 < 0;
}


bool pathContainsLocation(PathData* pathData, Location* location) {
    return pathData->location1 == location || pathData->location2 == location;
}

Location* getOtherEnd(PathData* pathData, Location* location) {
    if (pathData->location1 == location) {
        return pathData->location2;
    }
    if (pathData->location2 == location) {
        return pathData->location1;
    }
    return NULL;
}

bool moveAlongPath(PathData* pathData) {
    float destX = pathData->location2->x;
    float destY = pathData->location2->y;
    float destAngleRadian = pathData->angleRadian2;
    float dist1 = pathData->controlPointDistance1;
    float dist2 = pathData->controlPointDistance2;
    return clientExtendedMotionBSplineAbsolute(destX, destY, destAngleRadian, dist1, dist2, pathData->accelerationFactor, pathData->speedFactor);
}

bool restartFromPositionToGoToPath(PathData* pathData, Point* robotPosition) {
    Point locationPoint;
    locationPoint.x = pathData->location1->x;
    locationPoint.y = pathData->location1->y;

    float distanceSinceDeparture = distanceBetweenPoints(&locationPoint, robotPosition);

    float dist1 = pathData->controlPointDistance1;
    if (dist1 < 0.0f) {        
        dist1 = pathData->controlPointDistance1 + distanceSinceDeparture;
        if (dist1 >= -10.0f) {
            // Minimum to do a good trajectory : TO BE CHECKED
            dist1 = -10.0f;
        }
    }
    else if (dist1 > 0.0f) {        
        dist1 = pathData->controlPointDistance1 - distanceSinceDeparture;
        if (dist1 <= 10.0f) {
            // Minimum to do a good trajectory : TO BE CHECKED
            dist1 = 10.0f;
        }
    }
    float dist2 = pathData->controlPointDistance2;
    
    float destX = pathData->location2->x;
    float destY = pathData->location2->y;
    float destAngleRadian = pathData->angleRadian2;

    return clientExtendedMotionBSplineAbsolute(destX, destY, destAngleRadian, dist1, dist2, pathData->accelerationFactor, pathData->speedFactor);
}