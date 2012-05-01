#include "gameStrategyList.h"
#include "gameStrategy.h"

#include "../../common/error/error.h"

/**
 * Strategy list.
 */
static GameStrategyList strategies;

void addStrategy(GameStrategy* strategy, char* strategyName) {
    unsigned char size = strategies.size;
	if (size < MAX_STRATEGY) {
		strategy->name = strategyName;
	    strategies.strategies[size] = strategy;
	    strategies.size++;
	}
	else {
		writeError(TOO_MUCH_STRATEGIES);
    }
}

GameStrategy* getStrategy(int index) {
    return strategies.strategies[index];
}

int getStrategyCount() {
    return strategies.size;
}
