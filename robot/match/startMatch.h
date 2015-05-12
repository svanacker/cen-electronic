#ifndef START_MATCH_H
#define START_MATCH_H

#include <stdbool.h>

#include "../../common/eeprom/eeprom.h"

#include "../robot.h"
#include "teamColor.h"

// forward declaration
struct StartMatch;
typedef struct StartMatch StartMatch;

/**
* Define a call back function which must be called during loopUntilStart.
*/
typedef void LoopUntilStartHandleFunction(void);

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
    /** The function which must be used to know if the match is started or not. */
    IsMatchStartedFunction* isMatchStartedFunction;
    /** The function which must be called when the robot wait for start (to be able to continue to manage instruction */
    LoopUntilStartHandleFunction* loopUntilStartHandleFunction;
    /** The Eeprom which store information for persistence. */
    Eeprom* startMatchEeprom;
    /** If we simulate the Start Match or not. */
    bool simulateStartedMatch;
};

/**
 * Initialize the start Match Detector function.
 * @param startMatchDetector the startMatchDetector structure.
 * @param isMatchStartedFunctionParam the real function which must be used to detect the start of the match.
 */
void initStartMatch(StartMatch* startMatch,
                    IsMatchStartedFunction* isMatchStartedFunctionParam,
                    LoopUntilStartHandleFunction* loopUntilStartHandleFunction,
                    Eeprom* startMatchEeprom);

void setSimulateStartedMatch(StartMatch* startMatch, bool value);

/**
* Wait before start, but call the function given in argument.
*/
void loopUntilStart(StartMatch* startMatch);

/**
* Test if the match is started or not.
* @return true if the match is started, false else.
*/
bool isStarted(StartMatch* startMatch);

/**
 * Fill the Robot Position structure with the initial position when having teamColor set.
 * @param robotPosition (IN) the structure to fill
 * @param teamColor the color for which we want the initial Position.
 */
void fillStartMatchPositionForColor(StartMatch* startMatch, RobotPosition* robotPosition, enum TeamColor teamColor);

/** 
 * Save into the Eeprom the startMatch position for a specific color.
 */
void saveMatchPositionForColor(StartMatch* startMatch, RobotPosition* robotPosition, enum TeamColor teamColor);

#endif
