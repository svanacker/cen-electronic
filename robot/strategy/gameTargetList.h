#ifndef GAME_TARGET_LIST_H
#define GAME_TARGET_LIST_H

#include "gameTarget.h"

/** The max limit of target count. */
#define MAX_TARGET 		10

/**
 * Tre struct defining a list of targets.
 */
typedef struct {
    /** An array of pointer on target. */
    GameTarget* targets[MAX_TARGET];
    /** the size of the list. */
    unsigned char size;
} GameTargetList;


/**
 * Add a target to the list.
 * @param target the target to add to the list
 */
void addGameTarget(GameTarget* target, char* name);

/**
 * Get the target at index.
 */
GameTarget* getGameTarget(int index);

/**
 * Get the count of targets.
 */
int getGameTargetCount();

#endif

