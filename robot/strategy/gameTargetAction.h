#ifndef GAME_TARGET_ACTION_H
#define GAME_TARGET_ACTION_H

// #include "gameTarget.h"

#include "../../common/commons.h"

#include "../../common/2d/2d.h"
#include "../../common/io/outputStream.h"

#include "../../navigation/location.h"

/**
 * Encapsulates the target action.
 */
typedef struct GameTargetAction {
	// Returns the first point which is needed to do the target Action
	Location* startLocation;
	// Returns the location of the target Action.
	Location* endLocation;
	// Back reference to Target
	// GameTarget* target;	
	// Time to achieve (in millisecond)
	int timeToAchieve;
} GameTargetAction;

/**
 * Print the detail of the target action.
 */
void printGameTargetAction(OutputStream* outputStream, GameTargetAction* targetAction);


#endif

