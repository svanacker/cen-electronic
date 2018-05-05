#include "gameStrategyContextDebug.h"

#include <stdlib.h>

#include "../../common/2d/2dDebug.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printTableWriter.h"
#include "../../common/io/printWriter.h"

#include "../../common/math/cenMath.h"

#include "../../navigation/locationListDebug.h"

#include "../../robot/strategy/teamColor.h"

#include "gameTargetListDebug.h"

#define GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH     30
#define GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH   15
#define GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH    10
#define GAME_STRATEGY_CONTEXT_LAST_COLUMN            0

void printGameStrategyContextPoint(OutputStream* outputStream, Point* point, char* propertyPointName, char* pointNameX, char* pointNameY) {
    if (point == NULL) {
        appendStringTableData(outputStream, propertyPointName, GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
        appendStringTableData(outputStream, "NULL", GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
        appendStringTableData(outputStream, "-", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
        appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);
    }
    else {
        appendStringTableData(outputStream, pointNameX, GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
        appendDecfTableData(outputStream, point->x, GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
        appendStringTableData(outputStream, "mm", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
        appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);

        appendStringTableData(outputStream, pointNameY, GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
        appendDecfTableData(outputStream, point->y, GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
        appendStringTableData(outputStream, "mm", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
        appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);
    }
}

void printGameStrategyContextLocation(OutputStream* outputStream, Location* location, char* locationPropertyName, char* locationNameX, char* locationNameY, char* locationName ) {
    if (location == NULL) {
        appendStringTableData(outputStream, locationPropertyName, GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
        appendStringTableData(outputStream, "NULL", GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
        appendStringTableData(outputStream, "-", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
        appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);
    }
    else {
        appendStringTableData(outputStream, locationNameX, GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
        appendDecfTableData(outputStream, location->x, GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
        appendStringTableData(outputStream, "mm", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
        appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);

        appendStringTableData(outputStream, locationNameY, GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
        appendDecfTableData(outputStream, location->y, GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
        appendStringTableData(outputStream, "mm", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
        appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);

        appendStringTableData(outputStream, locationName, GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
        appendStringTableData(outputStream, location->name, GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
        appendStringTableData(outputStream, "mm", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
        appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);
    }
}

void printGameStrategyContextTableHeader(OutputStream* outputStream) {
    println(outputStream);

    // Table Header
    appendTableHeaderSeparatorLine(outputStream);
    appendStringHeader(outputStream, "Key", GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Value", GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Unit", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);
    appendTableHeaderSeparatorLine(outputStream);
}

void printGameStrategyContext(OutputStream* outputStream, GameStrategyContext* context) {
    appendString(outputStream, "\nGameStrategyContext:");
    printGameStrategyContextTableHeader(outputStream);

    // GameStrategy->name
    appendStringTableData(outputStream, "Strategy->Name", GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
    if (context->gameStrategy != NULL) {
        appendStringTableData(outputStream, context->gameStrategy->name, GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    }
    else {
        appendStringTableData(outputStream, "NULL", GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    }
    appendStringTableData(outputStream, "-", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);

    // StrategyIndex
    appendStringTableData(outputStream, "strategyIndex", GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, context->strategyIndex, GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);

    // TeamColor
    appendStringTableData(outputStream, "color", GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
    addTeamColorTableData(outputStream, context->color, GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);

    // elapsedMatchTime
    appendStringTableData(outputStream, "elapsedMatchTime", GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
    appendDecfTableData(outputStream, context->elapsedMatchTime, GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "seconds", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);

    // global Score
    appendStringTableData(outputStream, "Global Score", GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, context->score, GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "points", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);

    // Robot Position
    appendTableHeaderSeparatorLine(outputStream);
    // -> X / Y
    printGameStrategyContextPoint(outputStream, context->robotPosition, "robotPosition", "robotPosition.x", "robotPosition.y");
    // -> Angle
    appendStringTableData(outputStream, "robotPosition.angle", GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
    appendDecfTableData(outputStream, radToDeg(context->robotAngleRadian), GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "Degree", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);
    appendTableHeaderSeparatorLine(outputStream);

    // Robot Position
    printGameStrategyContextPoint(outputStream, context->opponentRobotPosition, "opponentRobotPosition", "opponentRobotPosition.x", "opponentRobotPosition.y");
    appendTableHeaderSeparatorLine(outputStream);

    // Obstacle Position
    printGameStrategyContextPoint(outputStream, context->lastObstaclePosition, "lastObstaclePosition", "lastObstaclePosition.x", "lastObstaclePosition.y");
    appendTableHeaderSeparatorLine(outputStream);

    // nearestLocation
    printGameStrategyContextLocation(outputStream, context->nearestLocation, "nearestLocation", "nearestLocation.x", "nearestLocation.y", "nearestLocation.name");

    // timeSinceLastCollision
    appendStringTableData(outputStream, "Time Since Last Collision", GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
    appendDecfTableData(outputStream, context->timeSinceLastCollision, GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "seconds", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);

    // Max target to Handle
    appendStringTableData(outputStream, "maxTargetToHandle", GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
    appendDecfTableData(outputStream, context->maxTargetToHandle, GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);

    // hasMoreNextSteps
    appendStringTableData(outputStream, "hasMoreNextSteps", GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
    appendDecfTableData(outputStream, context->hasMoreNextSteps, GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);

    appendTableHeaderSeparatorLine(outputStream);
    println(outputStream);

    // current Target
    /*
    appendString(outputStream, "\n\tcurrentTarget=");
    if (context->currentTarget != NULL) {
    // TODO printGameTargetTable(outputStream, context->currentTarget, false);
    }
    else {
    appendString(outputStream, "NULL");
    }
    */

    // currentTrajectory
    /*
    if (context->currentTrajectory != NULL) {
        printLocationListTable(outputStream, context->currentTrajectory);
    }
    else {
        appendString(outputStream, "\n\tcurrentTrajectory=NULL");
    }
    */
}
