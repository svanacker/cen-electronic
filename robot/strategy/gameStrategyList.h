#ifndef GAME_STRATEGY_LIST_H
#define GAME_STRATEGY_LIST_H

#include "gameStrategy.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

/** The max limit of strategy count. */
#define MAX_STRATEGY         1

/**
 * Tre struct defining a list of strategies.
 */
typedef struct {
    /** An array of pointer on strategy. */
    GameStrategy* strategies[MAX_STRATEGY];
    /** the size of the list. */
    unsigned char size;
} GameStrategyList;

void clearGameStrategies();

/**
 * Add a strategy to the list.
 * @param strategy the strategy to add to the list
 */
void addGameStrategy(GameStrategy* strategy, char* name);

/**
 * Get the strategy at index.
 */
GameStrategy* getGameStrategy(int index);

/**
 * Get the count of strategies.
 */
int getGameStrategyCount();

/**
 * Print the game strategy list, and for each the detail of strategy game
 */
void printGameStrategyList(OutputStream* outputStream);

#endif

