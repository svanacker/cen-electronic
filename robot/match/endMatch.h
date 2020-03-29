#ifndef END_MATCH_H
#define END_MATCH_H

#include <stdbool.h>

// forward declaration
struct EndMatch;
typedef struct EndMatch EndMatch;

#include "../../common/io/outputStream.h"
#include "../../common/timer/cenTimer.h"

#include "../../robot/config/robotConfig.h"

/** We take 1 seconds to be sure that it will be ok. */
#define MATCH_DURATION                    98

/** When the last Action Time must be done */
#define MATCH_LAST_ACTION_TIME            MATCH_DURATION - 3

// Forward declaration
struct EndMatch;
typedef struct EndMatch EndMatch;

/**
 * Type of function to do just before the end of the match
 */
typedef bool EndMatchBeforeEndFunction(EndMatch* endMatch);

/**
 * All elements to manage the end of the match
 */
struct EndMatch {
    /** To get the configuration. */
    RobotConfig* robotConfig;
    /** The match duration. */
    int matchDurationInSecond;
    /** Current Time In Second. */
    int currentTimeInSecond;
    /** Avoid that it does not take any instruction at the end. */
    bool doNotEnd;
    /** The timer struct to detect the end of the match. */
    Timer* endMatchDetectorDeviceTimer;
    /** If we have shown that the match was ended. */
    bool endOfMatchNotified;
    /** The score which must be shown. */
    unsigned int scoreToShow;
    /** If we show the score at the end. */
    bool showScoreAtTheEndOfMatch;
    /** What we must do some seconds before the end of the match */
    EndMatchBeforeEndFunction* endMatchBeforeEndFunction;
    /** If we have done the action before the end of the match */
    bool actionBeforeEndOfMatchDone;
};

/**
 * Initializes the end Match structure.
 */
void initEndMatch(EndMatch* endMatch, 
                  RobotConfig* robotConfig,
                  unsigned int matchDurationInSecond,
                  EndMatchBeforeEndFunction* endMatchBeforeEndFunction);

/**
 * Start the match.
 */
void markStartMatch(EndMatch* endMatch);

/**
 * Reset the match.
 */
void resetStartMatch(EndMatch* endMatch);

/**
 * Show the remaining time (before clear the screen).
 * @param endMatch
 * @param outputStream
 */
void showRemainingTime(EndMatch* endMatch, OutputStream* outputStream);

/**
 * Show to an output Stream the result of the match.
 * @return true if we have shown the end of the match
 */
void showEndAndScore(EndMatch* endMatch, OutputStream* outputStream);

/**
 * Show to an output Stream the result of the match, but only if needed (if endMatch is not finished and not already shown)
 * @return true if we have shown the end of the match
 */
bool showEndAndScoreIfNeeded(EndMatch* endMatch, OutputStream* outputStream);

/**
 * Returns how much time was passed.
 */
int getCurrentTimeInSecond(EndMatch* endMatch);

/**
 * Returns how much time in seconds are remaining
 */
unsigned int matchEndGetRemainingTime(EndMatch* endMatch);

/**
 * Return true if this is the end of the match.
 */
bool isMatchFinished(EndMatch* endMatch);

/**
* Returns true if this is just before the end of the match.
*/
bool isMatchJustBeforeTheEnd(EndMatch* endMatch);

/**
* Do the action before the end of the match if we expect it.
* @param endMatch 
*/
bool doActionBeforeEndOfMatch(EndMatch* endMatch, OutputStream* outputStream);

#endif