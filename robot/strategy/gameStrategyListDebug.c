#include "gameStrategyListDebug.h"
#include "gameStrategyList.h"
#include "gameStrategy.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

// DEBUG AS TABLE

#define STRATEGY_LIST_ID_COLUMN_LENGTH                12
#define STRATEGY_LIST_NAME_COLUMN_LENGTH              20
#define STRATEGY_LIST_LOCATION_LAST_COLUMN_LENGTH     48

void printStrategyListHeader(OutputStream* outputStream) {
	println(outputStream);
	// Table Header
	appendTableHeaderSeparatorLine(outputStream);
    appendStringHeader(outputStream, "Id", STRATEGY_LIST_ID_COLUMN_LENGTH);
    appendStringHeader(outputStream, "name", STRATEGY_LIST_NAME_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, STRATEGY_LIST_LOCATION_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);
}

/**
 * @private
*/
void printGameStrategy(OutputStream* outputStream, GameStrategy* gameStrategy) {
    appendDecTableData(outputStream, gameStrategy->strategyId, STRATEGY_LIST_ID_COLUMN_LENGTH);
    appendStringTableData(outputStream, gameStrategy->name, STRATEGY_LIST_NAME_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, STRATEGY_LIST_LOCATION_LAST_COLUMN_LENGTH);
}

void printGameStrategyTableList(OutputStream* outputStream) {
    int i;
    GameStrategyList* gameStrategyList = getGameStrategyList();
    int size = gameStrategyList->size;
	printStrategyListHeader(outputStream);
    for (i = 0; i < size; i++) {
        GameStrategy* strategy = gameStrategyList->strategies[i];
        printGameStrategy(outputStream, strategy);
    }
	appendTableHeaderSeparatorLine(outputStream);
}
