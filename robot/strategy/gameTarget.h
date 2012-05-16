#ifndef GAME_TARGET_H
#define GAME_TARGET_H

#include "gameTargetActionList.h"

#include "../../common/commons.h"

#include "../../common/io/outputStream.h"

#include "../../navigation/location.h"

#define TARGET_AVAILABLE 0
#define TARGET_HANDLED   1
#define TARGET_INUSE     2

/**
 * Encapsulates the target.
 */
typedef struct GameTarget {
	// Returns the name of the target.
	char* name;
	// Returns the gain when reaching a such target.
	float gain;
	// availability status of the target
	char status;	
	// Returns the position of the target on the gameboard
	Location* location;
	/** The actionList for this target. */
	GameTargetActionList actionList;
} GameTarget;

/**
 * Clear the game Target and actionList if any.
 */
void clearGameTarget(GameTarget* target);

/**
 * Print the detail of each target.
 */
void printGameTarget(OutputStream* outputStream, GameTarget* target, BOOL includeItems);


#endif

