#include "gameStrategyItemList.h"
#include "gameStrategyItem.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void addGameStrategyItem(GameStrategyItemList* gameStrategyItemList, GameStrategyItem* strategyItem) {
    unsigned char size = gameStrategyItemList->size;
	if (size < MAX_STRATEGY_ITEM) {
	    gameStrategyItemList->items[size] = strategyItem;
	    gameStrategyItemList->size++;
	}
	else {
		writeError(TOO_MUCH_STRATEGIES);
    }
}

GameStrategyItem* getStrategyItem(GameStrategyItemList* gameStrategyItemList, int index) {
    return gameStrategyItemList->items[index];
}

int getStrategyItemCount(GameStrategyItemList* gameStrategyItemList) {
    return gameStrategyItemList->size;
}

void printGameStrategyItemList(OutputStream* outputStream, GameStrategyItemList* gameStrategyItemList) {
	int i;
	int size = gameStrategyItemList->size;
	println(outputStream);	
	for (i = 0; i < size; i++) {
		GameStrategyItem* strategyItem = gameStrategyItemList->items[i];
		printGameStrategyItem(outputStream, strategyItem);
	}
}
