#ifndef GAME_TARGET_LIST_H
#define GAME_TARGET_LIST_H

#include "gameTarget.h"

#include "../../common/io/outputStream.h"

#include "../../navigation/location.h"

/** The max limit of target count. */
#define MAX_TARGET 		10

/**
 * Tre struct defining a list of targets.
 */
typedef struct {
    /** An array of pointer on target. */
    GameTarget* targets[MAX_TARGET];
	/** Number of target handled count. */
	unsigned char targetHandledCount;
    /** the size of the list. */
    unsigned char size;
} GameTargetList;

/**
 * Returns the global target list (singleton).
 */
GameTargetList* getGameTargetList();

/**
 * Clear the targets.
 */
void clearGameTargets();

/**
 * Register that we handle a target.
 */
void incTargetHandledCount();

/**
 * Returns the count of handled targets.
 */
unsigned char getTargetHandledCount();

/**
 * Add a target to the list.
 * @param target the target to add to the list
 */
void addGameTarget(GameTarget* target, char* name, int gain, Location* location);

/**
 * Get the target at index.
 */
GameTarget* getGameTarget(int index);

/**
 * Get the count of targets.
 */
int getGameTargetCount();

/**
 * Returns if there is available targets.
 */
BOOL containsAvailableTarget();

// DEBUG

/**
 * Print the game target list, and for each the detail of target.
 */
void printGameTargetList(OutputStream* outputStream);


#endif

