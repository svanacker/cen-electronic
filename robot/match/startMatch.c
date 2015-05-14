#include "startMatch.h"
#include "endMatchDetectorDevice.h"

#include <stdbool.h>
#include "../../common/eeprom/eepromAreas.h"

#include "../../common/log/logHandler.h"
#include "../../common/log/logger.h"

#define EEPROM_START_MATCH_ROBOT_POSITION_X_OFFSET         0
#define EEPROM_START_MATCH_ROBOT_POSITION_Y_OFFSET         6
#define EEPROM_START_MATCH_ROBOT_POSITION_ANGLE_OFFSET    12

#define EEPROM_START_MATCH_ROBOT_POSITION_BLOCK_SIZE      20

void setSimulateStartedMatch(StartMatch* startMatch, bool value) {
    startMatch->simulateStartedMatch = value;
    if (startMatch->simulateStartedMatch) {
        markStartMatch();
    }
    else {
        resetStartMatch();
    }
}

int getStartMatchDetectorEepromGetOffset(enum TeamColor teamColor) {
    int result = EEPROM_START_MATCH_START_INDEX + teamColor * EEPROM_START_MATCH_ROBOT_POSITION_BLOCK_SIZE;
    return result;
}

void fillStartMatchPositionForColor(StartMatch* startMatch, RobotPosition* robotPosition, enum TeamColor teamColor) {
    int globalOffset = getStartMatchDetectorEepromGetOffset(teamColor);
    Eeprom* startMatchEeprom = startMatch->startMatchEeprom;
    int x = eepromReadInt(startMatchEeprom, globalOffset + EEPROM_START_MATCH_ROBOT_POSITION_X_OFFSET);
    int y = eepromReadInt(startMatchEeprom, globalOffset + EEPROM_START_MATCH_ROBOT_POSITION_Y_OFFSET);
    int angleDeciDeg = eepromReadInt(startMatchEeprom, globalOffset + EEPROM_START_MATCH_ROBOT_POSITION_ANGLE_OFFSET);
    robotPosition->x = x;
    robotPosition->y = y;
    robotPosition->angleDeciDeg = angleDeciDeg;
}

void saveMatchPositionForColor(StartMatch* startMatch, RobotPosition* robotPosition, enum TeamColor teamColor) {
    int globalOffset = getStartMatchDetectorEepromGetOffset(teamColor);
    Eeprom* startMatchEeprom = startMatch->startMatchEeprom;
    eepromWriteInt(startMatchEeprom, globalOffset + EEPROM_START_MATCH_ROBOT_POSITION_X_OFFSET, robotPosition->x);
    eepromWriteInt(startMatchEeprom, globalOffset + EEPROM_START_MATCH_ROBOT_POSITION_Y_OFFSET, robotPosition->y);
    eepromWriteInt(startMatchEeprom, globalOffset + EEPROM_START_MATCH_ROBOT_POSITION_ANGLE_OFFSET, robotPosition->angleDeciDeg);
}


void loopUntilStart(StartMatch* startMatch) {
    if (startMatch == NULL) {
        return;
    }
    appendString(getAlwaysOutputStreamLogger(), "WAIT FOR START ...");
    while (startMatch->isMatchStartedFunction(startMatch)) {
        startMatch->loopUntilStartHandleFunction(startMatch);
    }
    appendString(getAlwaysOutputStreamLogger(), "OK\n");
}

bool isStarted(StartMatch* startMatch) {
    if (startMatch->simulateStartedMatch) {
        return true;
    }
    if (startMatch == NULL) {
        return false;
    }
    bool result = startMatch->isMatchStartedFunction(startMatch);
    return result;
}

void initStartMatch(StartMatch* startMatch,
                            IsMatchStartedFunction* isMatchStartedFunctionParam,
                            LoopUntilStartHandleFunction* loopUntilStartHandleFunction,
                            Eeprom* startMatchEeprom) {
    startMatch->isMatchStartedFunction = isMatchStartedFunctionParam;
    startMatch->loopUntilStartHandleFunction = loopUntilStartHandleFunction;
    startMatch->startMatchEeprom = startMatchEeprom;
}

