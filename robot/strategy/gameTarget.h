#ifndef GAME_TARGET_H
#define GAME_TARGET_H

#include <stdbool.h>

#include "gameTargetStatus.h"
#include "gameTargetActionList.h"

#include "../../common/io/outputStream.h"

#include "../../navigation/location.h"

/**
 * Encapsulates the target for a game.
 */
typedef struct GameTarget {
    // Returns the name of the target.
    char* name;
    // Returns the gain when reaching a such target.
    float potentialGain;
	// Returns the real gain that we actually have
	float gain;
    // Returns the current estimation (by calling computeBestNextTarget before)
    float currentComputedOpportunityFactor;
    // availability status of the target
    enum GameTargetStatus status;    
    // Returns the start Location (for the beginning of actions) 
    Location* startLocation;
    // Returns the end Location (for the end of actions)
    Location* endLocation;
    /** The actionList for this target. */
    GameTargetActionList actionList;
} GameTarget;

/**
 * Clear the game Target and actionList if any.
 */
void clearGameTarget(GameTarget* target);

/**
* Update the status of the target. 
*/
void updateTargetStatus(GameTarget* target);

#endif

