#include "gameStrategy.h"
#include "gameStrategyItem.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void addGameStrategyItem(GameStrategy* gameStrategy, GameStrategyItem* strategyItem) {
    unsigned char size = gameStrategy->size;
	if (size < MAX_STRATEGY_ITEM) {
	    gameStrategy->items[size] = strategyItem;
	    gameStrategy->size++;
	}
	else {
		writeError(TOO_MUCH_STRATEGIES);
    }
}

GameStrategyItem* getStrategyItem(GameStrategy* gameStrategy, int index) {
    return gameStrategy->items[index];
}

int getStrategyItemCount(GameStrategy* gameStrategy) {
    return gameStrategy->size;
}

void printGameStrategy(OutputStream* outputStream, GameStrategy* gameStrategy) {
	appendKeyAndName(outputStream, "strategy.name=", gameStrategy->name);
	println(outputStream);
	int size = gameStrategy->size;
	int i;
	for (i = 0; i < size; i++) {
		GameStrategyItem* strategyItem = gameStrategy->items[i];
		printGameStrategyItem(outputStream, strategyItem);
	}

}
