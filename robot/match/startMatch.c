#include "startMatch.h"
#include "endMatch.h"

#include <stdbool.h>
#include "../../common/2d/2d.h"

#include "../../common/eeprom/eeprom.h"
#include "../../common/eeprom/eepromAreas.h"

#include "../../common/log/logHandler.h"
#include "../../common/log/logger.h"

#define EEPROM_START_MATCH_ROBOT_POSITION_X_OFFSET         0
#define EEPROM_START_MATCH_ROBOT_POSITION_Y_OFFSET         6
#define EEPROM_START_MATCH_ROBOT_POSITION_ANGLE_OFFSET    12

#define EEPROM_START_MATCH_ROBOT_POSITION_BLOCK_SIZE      20

void setSimulateStartedMatch(StartMatch* startMatch, bool value) {
    EndMatch* endMatch = startMatch->endMatch;
    startMatch->simulateStartedMatch = value;
    if (startMatch->simulateStartedMatch) {
        markStartMatch(endMatch);
    }
    else {
        resetStartMatch(endMatch);
    }
}

unsigned long getStartMatchDetectorEepromGetOffset(enum TeamColor teamColor) {
    unsigned long result = EEPROM_START_MATCH_START_INDEX + teamColor * EEPROM_START_MATCH_ROBOT_POSITION_BLOCK_SIZE;
    return result;
}

void fillStartMatchPositionForColor(StartMatch* startMatch, RobotPosition* robotPosition, enum TeamColor teamColor) {
    unsigned long globalOffset = getStartMatchDetectorEepromGetOffset(teamColor);
    Eeprom* startMatchEeprom = startMatch->startMatchEeprom;
    float x = eepromReadUnsignedFloat(startMatchEeprom, globalOffset + EEPROM_START_MATCH_ROBOT_POSITION_X_OFFSET, POSITION_DIGIT_MM_PRECISION);
    float y = eepromReadUnsignedFloat(startMatchEeprom, globalOffset + EEPROM_START_MATCH_ROBOT_POSITION_Y_OFFSET, POSITION_DIGIT_MM_PRECISION);
    float angleDegree = eepromReadUnsignedFloat(startMatchEeprom, globalOffset + EEPROM_START_MATCH_ROBOT_POSITION_ANGLE_OFFSET, ANGLE_DIGIT_DEGREE_PRECISION);
    robotPosition->x = x;
    robotPosition->y = y;
    robotPosition->angleDegree = angleDegree;
}

void saveMatchPositionForColor(StartMatch* startMatch, RobotPosition* robotPosition, enum TeamColor teamColor) {
    int globalOffset = getStartMatchDetectorEepromGetOffset(teamColor);
    Eeprom* startMatchEeprom = startMatch->startMatchEeprom;
    eepromWriteUnsignedFloat(startMatchEeprom, globalOffset + EEPROM_START_MATCH_ROBOT_POSITION_X_OFFSET, robotPosition->x, POSITION_DIGIT_MM_PRECISION);
    eepromWriteUnsignedFloat(startMatchEeprom, globalOffset + EEPROM_START_MATCH_ROBOT_POSITION_Y_OFFSET, robotPosition->y, POSITION_DIGIT_MM_PRECISION);
    eepromWriteUnsignedFloat(startMatchEeprom, globalOffset + EEPROM_START_MATCH_ROBOT_POSITION_ANGLE_OFFSET, robotPosition->angleDegree, ANGLE_DIGIT_DEGREE_PRECISION);
}


void loopUntilStart(StartMatch* startMatch) {
    if (startMatch == NULL) {
        return;
    }
    appendString(getAlwaysOutputStreamLogger(), "WAIT FOR START ...");
    while (!startMatch->isMatchStartedFunction(startMatch)) {
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
                    RobotConfig* robotConfig,
                    EndMatch* endMatch,
                    IsMatchStartedFunction* isMatchStartedFunctionParam,
                    LoopUntilStartHandleFunction* loopUntilStartHandleFunction,
                    Eeprom* startMatchEeprom) {
    startMatch->robotConfig = robotConfig;
    startMatch->endMatch = endMatch;
    startMatch->isMatchStartedFunction = isMatchStartedFunctionParam;
    startMatch->loopUntilStartHandleFunction = loopUntilStartHandleFunction;
    startMatch->startMatchEeprom = startMatchEeprom;
}

