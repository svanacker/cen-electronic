#ifndef GAME_TARGET_H
#define GAME_TARGET_H

#include "gameTargetActionList.h"

#include "../../common/commons.h"

#include "../../common/2d/2d.h"
#include "../../common/io/outputStream.h"

/**
 * Encapsulates the target.
 */
typedef struct GameTarget {
	// Returns the name of the target.
	char* name;
	// Returns the gain when reaching a such target.
	float gain;
	// Checks whether the target is still available
	BOOL available;	
	// Returns the position of the target on the gameboard
	Point point;
	/** The actionList for this target. */
	GameTargetActionList actionList;
} GameTarget;

/**
 * Print the detail of each target.
 */
void printGameTarget(OutputStream* outputStream, GameTarget* target);


#endif

