#include <stdlib.h>

#include "gameStrategyContext.h"

#include "../../navigation/locationList.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void printGameStrategyContext(OutputStream* outputStream, GameStrategyContext* context) {
    appendString(outputStream, "GameStrategyContext\n");
    appendString(outputStream, "\tstrategy.name=");

    // gameStrategy
    if (context->gameStrategy != NULL) {
        appendString(outputStream, context->gameStrategy->name);
    }
    else {
        appendString(outputStream, "NULL");
    }

    // elapsedMatchTime
    appendStringAndDecf(outputStream, "\n\telapsedMatchTime=", context->elapsedMatchTime);
    println(outputStream);
    
    // Robot Position
    appendString(outputStream, "\trobotPosition=");
    printPoint(outputStream, &(context->robotPosition), "");
    appendStringAndDec(outputStream, "\n\trobotAngle (ddeg)=", context->robotAngle);

    // nearestLocation
    appendString(outputStream, "\n\tnearestLocation=");
    if (context->nearestLocation != NULL) {
        printLocation(outputStream, context->nearestLocation);
    }
    else {
        appendString(outputStream, "NULL");
    }

    appendStringAndDec(outputStream, "\ntimeSinceLastCollision=", context->timeSinceLastCollision);
    // Robot Position
    appendString(outputStream, "\n\topponentRobotPosition=");
    printPoint(outputStream, &(context->opponentRobotPosition), "");

    // Obstacle Position
    appendString(outputStream, "\n\tlastObstaclePosition=");
    printPoint(outputStream, &(context->lastObstaclePosition), "");

    // current Target
    appendString(outputStream, "\n\tcurrentTarget=");
    if (context->currentTarget != NULL) {
        printGameTarget(outputStream, context->currentTarget, false);
    }
    else {
        appendString(outputStream, "NULL");
    }

    // currentTrajectory
    if (&(context->currentTrajectory) != NULL) {
        printLocationListTable(outputStream, &(context->currentTrajectory));
    }
    else {
        appendString(outputStream, "\n\tcurrentTrajectory=NULL");
    }
    appendStringAndDec(outputStream, "\n\tteamColor=", context->color);
    appendStringAndDec(outputStream, "\n\tstrategyIndex=", context->strategyIndex);
    appendStringAndDec(outputStream, "\n\tmaxTargetToHandle=", context->maxTargetToHandle);

//    appendStringAndDec(outputStream, "\n\tmustDoNextStep=", context->mustDoNextStep);
    appendStringAndDec(outputStream, "\n\thasMoreNextSteps=", context->hasMoreNextSteps);

    println(outputStream);
}
