#include <stdlib.h>

#include "path.h"
#include "location.h"

#include "../common/commons.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

// TODO : TO REMOVE
#include "../robot/2012/strategy2012Utils.h"

int getAngle1Path(PathData* pathData) {
    int angle1 = pathData->angle1;
    int result = changeAngleForColor(angle1);
    return result;
}

int getAngle2Path(PathData* pathData) {
    int angle2 = pathData->angle2;
    int result = changeAngleForColor(angle2);
    return result;
}

void fillPathData(PathData* pathData, 
                    Location* location1,
                     Location* location2, 
                     int cost,
                     int controlPointDistance1,
                     int controlPointDistance2,
                     int angle1,
                     int angle2,
                     unsigned char accelerationFactor,
                     unsigned char speedFactor) {
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

void fillAsymmetricPathData(
                      PathData* pathData,
                     Location* location1,
                     Location* location2, 
                     int cost,
                     int controlPointDistance1,
                     int controlPointDistance2,
                     int angle1,
                     int angle2,
                     unsigned char accelerationFactor,
                     unsigned char speedFactor) {
    fillPathData(pathData, location1, location2, cost, controlPointDistance1, controlPointDistance2, angle1, angle2, accelerationFactor, speedFactor);
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

    appendStringAndDec(outputStream, ", cost=", pathData->cost);

    appendStringAndDec(outputStream, ", controlPointDist1=", pathData->controlPointDistance1);
    appendStringAndDec(outputStream, ", controlPointDist2=", pathData->controlPointDistance2);

    appendStringAndDec(outputStream, ", angle1=", getAngle1Path(pathData));
    appendStringAndDec(outputStream, ", angle2=", getAngle2Path(pathData));

    appendStringAndDec(outputStream, ", accFactor=", pathData->accelerationFactor);
    appendStringAndDec(outputStream, ", speedFactor=", pathData->speedFactor);
    appendString(outputStream, ", mustGoBackward=");
    appendBoolAsString(outputStream, pathData->mustGoBackward);

    println(outputStream);
}
