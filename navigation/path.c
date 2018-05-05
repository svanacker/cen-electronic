#include <stdlib.h>

#include "path.h"
#include "location.h"

#include "../common/commons.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

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
    pathData->mustGoBackward = true;
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