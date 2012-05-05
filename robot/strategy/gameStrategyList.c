#include "gameStrategyList.h"
#include "gameStrategy.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

/**
 * Strategy list.
 */
static GameStrategyList strategies;

void addGameStrategy(GameStrategy* strategy, char* strategyName) {
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

void printGameStrategyList(OutputStream* outputStream) {
	int i;
	int size = strategies.size;
	println(outputStream);	
	for (i = 0; i < size; i++) {
		GameStrategy* strategy = strategies.strategies[i];
		printGameStrategy(outputStream, strategy);
	}
}
