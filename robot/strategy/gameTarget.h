#ifndef GAME_TARGET_H
#define GAME_TARGET_H

#include <stdbool.h>

#include "gameTargetStatus.h"
#include "gameTargetActionList.h"

#include "../../common/io/outputStream.h"

#include "../../navigation/location.h"

// forward declaration
struct GameTarget;
typedef struct GameTarget GameTarget;

/**
 * Encapsulates the target for a game.
 */
struct GameTarget {
    // Returns the name of the target.
    char* name;
    // Returns the gain when reaching a such target.
    float potentialGain;
	// Returns the real gain that we actually have
	float gain;
    // availability status of the target
    enum GameTargetStatus status;    
    // Returns the position of the target on the gameboard
    Location* location;
    /** The actionList for this target. */
    GameTargetActionList actionList;
};

/**
 * Clear the game Target and actionList if any.
 */
void clearGameTarget(GameTarget* target);

#endif

