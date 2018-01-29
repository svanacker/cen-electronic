#include "gameStrategy.h"
#include "gameStrategyItem.h"
#include "gameTarget.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"


void clearGameStrategy(GameStrategy* gameStrategy) {
    gameStrategy->size = 0;
}

void addGameStrategyItem(GameStrategy* gameStrategy,
                         GameStrategyItem* strategyItem,
                         GameTarget* target
) {
    unsigned char size = gameStrategy->size;
    if (size < MAX_STRATEGY_ITEM) {
        strategyItem->target = target;
        gameStrategy->items[size] = strategyItem;
        gameStrategy->size++;
    }
    else {
        writeError(TOO_MUCH_STRATEGY_ITEMS);
    }
}

GameStrategyItem* getStrategyItem(GameStrategy* gameStrategy, int index) {
    return gameStrategy->items[index];
}

int getStrategyItemCount(GameStrategy* gameStrategy) {
    return gameStrategy->size;
}


// DEBUG AS TABLE

#define GAME_STRATEGY_ITEM_LIST_TARGET_NAME_COLUMN_LENGTH     12
#define GAME_STRATEGY_ITEM_LIST_LAST_COLUMN_LENGTH            37

/**
* Private.
*/
void printGameStrategyItemListHeader(OutputStream* outputStream) {
	println(outputStream);
	// Table Header
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "target->name", GAME_STRATEGY_ITEM_LIST_TARGET_NAME_COLUMN_LENGTH);

    appendEndOfTableColumn(outputStream, GAME_STRATEGY_ITEM_LIST_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);
}

/**
* @private
*/
void printGameStrategyItem(OutputStream* outputStream, GameStrategyItem* strategyItem) {
	GameTarget* target = strategyItem->target;
	appendStringTableData(outputStream, target->name, GAME_STRATEGY_ITEM_LIST_TARGET_NAME_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, GAME_STRATEGY_ITEM_LIST_LAST_COLUMN_LENGTH);
}

void printGameStrategyTable(OutputStream* outputStream, GameStrategy* gameStrategy) {
	int size = gameStrategy->size;
	int i;
	for (i = 0; i < size; i++) {
		GameStrategyItem* strategyItem = gameStrategy->items[i];
		printGameStrategyItem(outputStream, strategyItem);
	}
}
