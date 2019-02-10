#include "mainBoardCommonMatch.h"

#include "../../device/deviceList.h"

#include "../../robot/match/startMatch.h"
#include "../../robot/match/endMatch.h"
#include "../../robot/match/startMatchDevice.h"
#include "../../robot/match/startMatchDeviceInterface.h"
#include "../../robot/match/endMatchDetectorDevice.h"
#include "../../robot/match/endMatchDetectorDeviceInterface.h"

// StartMatch
static StartMatch startMatch;
static EndMatch endMatch;

void mainBoardCommonMatchAddDevices(void) {
    // START & END MATCH
    addLocalDevice(getStartMatchDeviceInterface(), getStartMatchDeviceDescriptor(&startMatch));
    addLocalDevice(getEndMatchDetectorDeviceInterface(), getEndMatchDetectorDeviceDescriptor(&endMatch));
}

void mainBoardCommonMatchLoopUntilStart(void) {
    loopUntilStart(&startMatch);
}

StartMatch* mainBoardCommonMatchGetStartMatch(void) {
    return &startMatch;
}

EndMatch* mainBoardCommonMatchGetEndMatch(void) {
    return &endMatch;
}

void mainBoardCommonMatchMainInitDrivers(RobotConfig* robotConfig, 
                                         IsMatchStartedFunction* isMatchStartedFunctionParam, 
                                         LoopUntilStartHandleFunction* loopUntilStartHandleFunction,
                                         MatchHandleInstructionFunction* matchHandleInstructionFunction) {
    initEndMatch(&endMatch, robotConfig, MATCH_DURATION);
    initStartMatch(&startMatch,
                   robotConfig,
                   &endMatch,
                   isMatchStartedFunctionParam,
                  loopUntilStartHandleFunction,
                matchHandleInstructionFunction);
}