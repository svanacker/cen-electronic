#ifndef START_MATCH_DETECTOR_H
#define START_MATCH_DETECTOR_H

#include <stdbool.h>

struct StartMatchDetector;
typedef struct StartMatchDetector StartMatchDetector;

/**
 * Call back function which must be called to detect if the match is started or not !
 * @param startMatchDetector the pointer on the structure.
 * @return true if the match has started, false else
 */
typedef bool IsMatchStartedFunction(StartMatchDetector* startMatchDetector);

struct StartMatchDetector {
    /** The function which must be used to know if the match is started or not. */
    IsMatchStartedFunction* isMatchStartedFunction;
};

/**
 * Initialize the start Match Detector function.
 * @param startMatchDetector the startMatchDetector structure.
 * @param isMatchStartedFunctionParam the real function which must be used to detect the start of the match.
 */
void initStartMatchDetector(StartMatchDetector* startMatchDetector, IsMatchStartedFunction* isMatchStartedFunctionParam);

#endif
