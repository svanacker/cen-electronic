#ifndef START_MATCH_H
#define START_MATCH_H

#include <stdbool.h>

#include "../../common/eeprom/eeprom.h"

#include "endMatch.h"

#include "../robot.h"

// forward declaration
struct StartMatch;
typedef struct StartMatch StartMatch;

/**
* Define a call back function which must be called during loopUntilStart.
* @param startMatch encapsulation of the information about the match
* @return true if it must continue, false if we must escape
*/
typedef bool LoopUntilStartHandleFunction(StartMatch* startMatch);

/**
* Define a call back function which must be called during match.
* @param startMatch encapsulation of the information about the match
* @return true if it must continue, false if we must escape
*/
typedef bool MatchHandleInstructionFunction(StartMatch* startMatch);

/**
 * Call back function which must be called to detect if the match is started or not !
 * @param startMatch the pointer on the structure.
 * @return true if the match has started, false else
 */
typedef bool IsMatchStartedFunction(StartMatch* startMatch);

/**
 * Define the Structure which stores all informations needed for StartMatch.
 */
struct StartMatch {
    /** To get the configuration. */
    RobotConfig* robotConfig;
    /** The function which must be used to know if the match is started or not. */
    IsMatchStartedFunction* isMatchStartedFunction;
    /** The function which must be called when the robot wait for start (to be able to continue to manage instruction */
    LoopUntilStartHandleFunction* loopUntilStartHandleFunction;
    /** The function which must be called during the match */
    MatchHandleInstructionFunction* matchHandleInstructionFunction;
    /** Pointer on the endMatch management */
    EndMatch* endMatch;
    /** Don't wait for start */
    bool waitForStart;
};

/**
 * Initialize the start Match Detector function.
 * @param startMatchDetector the startMatchDetector structure.
 * @param isMatchStartedFunctionParam the real function which must be used to detect the start of the match.
 * @param loopUntilStartHandleFunction the function which must be used before the start of match to Handle instruction
 * @param matchHandleInstructionFunction the function which must be called after the start of the match
 */
void initStartMatch(StartMatch* startMatch,
                    RobotConfig* robotConfig,
                    EndMatch* endMatch,
                    IsMatchStartedFunction* isMatchStartedFunctionParam,
                    LoopUntilStartHandleFunction* loopUntilStartHandleFunction,
                    MatchHandleInstructionFunction* matchHandleInstructionFunction);

/**
* Wait before start, but call the function given in argument.
*/
void loopUntilStart(StartMatch* startMatch);

/**
* Test if the match is started or not.
* @return true if the match is started, false else.
*/
bool isMatchStarted(StartMatch* startMatch);

#endif
