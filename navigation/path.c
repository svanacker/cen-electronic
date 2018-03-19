#include <stdlib.h>

#include "path.h"
#include "location.h"

#include "../common/commons.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

// TODO : TO REMOVE
#include "../robot/2012/strategy2012Utils.h"

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

void initPathData(PathData* pathData, 
                    Location* location1,
                     Location* location2, 
                     float cost,
                     float controlPointDistance1,
                     float controlPointDistance2,
                     float angle1,
                     float angle2,
                     float accelerationFactor,
                     float speedFactor) {
    pathData->location1 = location1;
    pathData->location2 = location2;
    pathData->controlPointDistance1 = controlPointDistance1;
    pathData->controlPointDistance2 = controlPointDistance2;
    pathData->angle1 = angle1;
    pathData->angle2 = angle2;
    pathData->cost = cost;
    pathData->accelerationFactor = accelerationFactor;
    pathData->speedFactor = speedFactor;
    pathData->mustGoBackward = false;
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

void printPath(OutputStream* outputStream, PathData* pathData) {
    appendString(outputStream, "pathName=");
    if (pathData->location1 == NULL) {
        append(outputStream, '?');
    }
    else {
        appendString(outputStream, pathData->location1->name);
    }
    appendString(outputStream, "->");
    if (pathData->location2 == NULL) {
        append(outputStream, '?');
    }
    else {
        appendString(outputStream, pathData->location2->name);
    }

    appendStringAndDecf(outputStream, ", cost=", pathData->cost);

    appendStringAndDecf(outputStream, ", controlPointDist1=", pathData->controlPointDistance1);
    appendStringAndDecf(outputStream, ", controlPointDist2=", pathData->controlPointDistance2);

    appendStringAndDecf(outputStream, ", angle1=", getAngle1Path(pathData));
    appendStringAndDecf(outputStream, ", angle2=", getAngle2Path(pathData));

    appendStringAndDecf(outputStream, ", accFactor=", pathData->accelerationFactor);
    appendStringAndDecf(outputStream, ", speedFactor=", pathData->speedFactor);
    appendString(outputStream, ", mustGoBackward=");
    appendBoolAsString(outputStream, pathData->mustGoBackward);

    println(outputStream);
}
