#include "gameStrategyDebug.h"
#include "gameStrategy.h"
#include "gameStrategyItem.h"
#include "gameTarget.h"
#include "gameTargetListDebug.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#define GAME_STRATEGY_ITEM_LIST_TARGET_NAME_COLUMN_LENGTH               12
#define GAME_STRATEGY_ITEM_LIST_TARGET_GAIN_COLUMN_LENGTH               12
#define GAME_STRATEGY_ITEM_LIST_TARGET_POTENTIAL_GAIN_COLUMN_LENGTH     15
#define GAME_STRATEGY_ITEM_LIST_TARGET_STATUS_COLUMN_LENGTH             12
#define GAME_STRATEGY_ITEM_LIST_LAST_COLUMN_LENGTH            37

/**
* Private.
*/
void printGameStrategyItemListHeader(OutputStream* outputStream) {
	println(outputStream);
	// Table Header
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "name", GAME_STRATEGY_ITEM_LIST_TARGET_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "gain", GAME_STRATEGY_ITEM_LIST_TARGET_GAIN_COLUMN_LENGTH);
    appendStringHeader(outputStream, "potentialGain", GAME_STRATEGY_ITEM_LIST_TARGET_POTENTIAL_GAIN_COLUMN_LENGTH);
    appendStringHeader(outputStream, "status", GAME_STRATEGY_ITEM_LIST_TARGET_STATUS_COLUMN_LENGTH);

    appendEndOfTableColumn(outputStream, GAME_STRATEGY_ITEM_LIST_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);
}

/**
* @private
*/
void printGameStrategyItem(OutputStream* outputStream, GameStrategyItem* strategyItem) {
	GameTarget* target = strategyItem->target;
	appendStringTableData(outputStream, target->name, GAME_STRATEGY_ITEM_LIST_TARGET_NAME_COLUMN_LENGTH);
    appendDecfTableData(outputStream, target->potentialGain, GAME_STRATEGY_ITEM_LIST_TARGET_NAME_COLUMN_LENGTH);
    addGameTargetStatusTableData(outputStream, target->status, GAME_STRATEGY_ITEM_LIST_TARGET_NAME_COLUMN_LENGTH);

    appendEndOfTableColumn(outputStream, GAME_STRATEGY_ITEM_LIST_LAST_COLUMN_LENGTH);
}

void printGameStrategyTable(OutputStream* outputStream, GameStrategy* gameStrategy) {
	int size = gameStrategy->size;
	int i;
    printGameStrategyItemListHeader(outputStream);
	for (i = 0; i < size; i++) {
		GameStrategyItem* strategyItem = gameStrategy->items[i];
		printGameStrategyItem(outputStream, strategyItem);
	}
    appendTableHeaderSeparatorLine(outputStream);
}
