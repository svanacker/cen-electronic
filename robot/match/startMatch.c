#include "startMatch.h"
#include "endMatch.h"

#include <stdbool.h>
#include "../../common/2d/2d.h"

#include "../../common/eeprom/eeprom.h"
#include "../../common/eeprom/eepromAreas.h"

#include "../../common/log/logHandler.h"
#include "../../common/log/logger.h"

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

