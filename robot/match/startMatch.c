#include "startMatch.h"
#include "endMatch.h"

#include <stdbool.h>

#include "../../common/2d/2d.h"

#include "../../common/error/error.h"

#include "../../common/eeprom/eeprom.h"
#include "../../common/eeprom/eepromAreas.h"

#include "../../common/log/logHandler.h"
#include "../../common/log/logger.h"

void loopUntilStart(StartMatch* startMatch) {
    if (startMatch == NULL) {
        writeError(ROBOT_START_MATCH_DETECTOR_PC_NULL);
        return;
    }
    if (startMatch->waitForStart) {
        appendString(getAlwaysOutputStreamLogger(), "WAIT START...");
        while (!startMatch->isMatchStartedFunction(startMatch)) {
            startMatch->loopUntilStartHandleFunction(startMatch);
        }
        appendString(getAlwaysOutputStreamLogger(), "OK");
        println(getAlwaysOutputStreamLogger());
        markStartMatch(startMatch->endMatch);
    }
    else {
        appendString(getAlwaysOutputStreamLogger(), "GO !");
        println(getAlwaysOutputStreamLogger());
    }
}

bool isMatchStarted(StartMatch* startMatch) {
    if (startMatch == NULL) {
        writeError(ROBOT_START_MATCH_DETECTOR_PC_NULL);
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
                    MatchHandleInstructionFunction* matchHandleInstructionFunction) {
    startMatch->robotConfig = robotConfig;
    startMatch->endMatch = endMatch;
    startMatch->isMatchStartedFunction = isMatchStartedFunctionParam;
    startMatch->loopUntilStartHandleFunction = loopUntilStartHandleFunction;
    startMatch->matchHandleInstructionFunction = matchHandleInstructionFunction;
    startMatch->waitForStart = !isConfigSet(robotConfig, CONFIG_DONT_WAIT_FOR_START);
}

