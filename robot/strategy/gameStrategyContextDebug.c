#include "gameStrategyContextDebug.h"

#include <stdlib.h>

#include "../../common/2d/2dDebug.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printTableWriter.h"
#include "../../common/io/printWriter.h"

#include "../../common/math/cenMath.h"

#include "../../motion/position/trajectoryTypeDebug.h"

#include "../../navigation/locationListDebug.h"

#include "../../robot/strategy/teamColor.h"

#include "gameTargetListDebug.h"

#define GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH     35
#define GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH   25
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
        appendFixedCharArrayTableData(outputStream, &(location->name), GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
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
    println(outputStream);
    appendString(outputStream, "GameStrategyContext:");
    printGameStrategyContextTableHeader(outputStream);

    // Simulation Mode
    appendStringTableData(outputStream, "simulation", GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
    appendBoolAsStringTableData(outputStream, context->simulateMove, GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);

    appendStringTableData(outputStream, "loopTargetAndActions", GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
    appendBoolAsStringTableData(outputStream, context->loopTargetAndActions, GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);

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
    appendStringTableData(outputStream, "strategyId", GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, context->strategyId, GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);
    appendTableHeaderSeparatorLine(outputStream);

    // Acceleration Factor
    appendStringTableData(outputStream, "Default Acc. Factor", GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
    appendDecfTableData(outputStream, context->defaultAccelerationFactor, GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);
    appendTableHeaderSeparatorLine(outputStream);

    // Acceleration Factor
    appendStringTableData(outputStream, "Default Speed Factor", GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
    appendDecfTableData(outputStream, context->defaultSpeedFactor, GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);
    appendTableHeaderSeparatorLine(outputStream);


    // TeamColor
    appendStringTableData(outputStream, "color", GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
    addTeamColorTableData(outputStream, context->color, GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "-", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);
    appendTableHeaderSeparatorLine(outputStream);

    // remainingTime
    appendStringTableData(outputStream, "endMatch->remainingTime", GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, matchEndGetRemainingTime(context->endMatch), GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "seconds", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);
    appendTableHeaderSeparatorLine(outputStream);

    // global Score
    appendStringTableData(outputStream, "Global Score", GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, context->endMatch->scoreToShow, GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "points", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);
    appendTableHeaderSeparatorLine(outputStream);

    // Robot Position
    appendTableHeaderSeparatorLine(outputStream);
    // -> X / Y
    printGameStrategyContextPoint(outputStream, context->robotPosition, "robotPosition", "robotPosition.x", "robotPosition.y");
    // -> Angle
    appendStringTableData(outputStream, "robotPosition.angle", GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
    appendDecfTableData(outputStream, radToDeg(context->robotAngleRadian), GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "Degree", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);
    // -> Trajectory Type
    appendStringTableData(outputStream, "trajectoryType", GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
    addTrajectoryTypeTableData(outputStream, context->trajectoryType, GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);

    appendStringTableData(outputStream, "Robot Position Update Int. Flag", GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
    appendBoolAsStringTableData(outputStream, context->robotPositionToUpdateInterruptFlag, GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);

    appendTableHeaderSeparatorLine(outputStream);

    // Robot Position
    printGameStrategyContextPoint(outputStream, context->opponentRobotPosition, "opponentRobotPosition", "opponentRobotPosition.x", "opponentRobotPosition.y");
    appendTableHeaderSeparatorLine(outputStream);

    // Obstacle Position
    printGameStrategyContextPoint(outputStream, context->lastObstaclePosition, "lastObstaclePosition", "lastObstaclePosition.x", "lastObstaclePosition.y");

    // timeSinceLastCollision
    appendStringTableData(outputStream, "Time Since Last Collision", GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
    appendDecfTableData(outputStream, context->timeSinceLastCollision, GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    appendStringTableData(outputStream, "seconds", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);

    appendTableHeaderSeparatorLine(outputStream);

    // nearestLocation
    printGameStrategyContextLocation(outputStream, context->nearestLocation, "nearestLocation", "nearestLocation.x", "nearestLocation.y", "nearestLocation.name");

    // Next Location
    appendStringTableData(outputStream, "nearestLocation->next", GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
    if (context->nearestLocation != NULL) {
        appendTableSeparator(outputStream);
        appendSpace(outputStream);
        unsigned int charCount = appendLocationLinkedPath(outputStream, context->nearestLocation);
        appendSpaces(outputStream, GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH - charCount);
    }
    else {
        appendStringTableData(outputStream, "NULL", GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    }
    appendStringTableData(outputStream, "-", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);

    // currentTarget->startLocation
    appendStringTableData(outputStream, "currentTarget->startLocation", GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
    GameTarget* currentTarget = context->currentTarget;
    if (currentTarget != NULL && currentTarget->startLocation != NULL) {
        appendFixedCharArrayTableData(outputStream, &(currentTarget->startLocation->name), GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    }
    else {
        appendStringTableData(outputStream, "NULL", GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    }
    appendStringTableData(outputStream, "-", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);

    // currentTarget->endLocation
    appendStringTableData(outputStream, "currentTarget->endLocation", GAME_STRATEGY_CONTEXT_KEY_COLUMN_LENGTH);
    if (currentTarget != NULL && currentTarget->endLocation != NULL) {
        appendFixedCharArrayTableData(outputStream, &(currentTarget->endLocation->name), GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    }
    else {
        appendStringTableData(outputStream, "NULL", GAME_STRATEGY_CONTEXT_VALUE_COLUMN_LENGTH);
    }
    appendStringTableData(outputStream, "-", GAME_STRATEGY_CONTEXT_UNIT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, GAME_STRATEGY_CONTEXT_LAST_COLUMN);

    appendTableHeaderSeparatorLine(outputStream);

    println(outputStream);

    // currentTrajectory
}
