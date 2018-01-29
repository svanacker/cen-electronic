#include "gameStrategyList.h"
#include "gameStrategy.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

/**
 * Strategy list.
 */
static GameStrategyList strategies;

void clearGameStrategies() {
    int size = strategies.size;
    int i;
    for (i = 0; i < size; i++) {
        GameStrategy* strategy = strategies.strategies[i];
        clearGameStrategy(strategy);
    }
    strategies.size = 0;
}

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

GameStrategy* getGameStrategy(int index) {
    return strategies.strategies[index];
}

int getGameStrategyCount(void) {
    return strategies.size;
}

// DEBUG AS TABLE

#define STRATEGY_LIST_INDEX_COLUMN_LENGTH             12
#define STRATEGY_LIST_NAME_COLUMN_LENGTH              12
#define STRATEGY_LIST_LOCATION_LAST_COLUMN_LENGTH     37

void printStrategyListHeader(OutputStream* outputStream) {
	println(outputStream);
	// Table Header
	appendTableHeaderSeparatorLine(outputStream);
    appendStringHeader(outputStream, "index", STRATEGY_LIST_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "name", STRATEGY_LIST_NAME_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, STRATEGY_LIST_LOCATION_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);
}

/**
 * @private
*/
void printGameStrategy(OutputStream* outputStream, GameStrategy* gameStrategy, int index) {
    appendStringTableData(outputStream, index, STRATEGY_LIST_INDEX_COLUMN_LENGTH);
    appendStringTableData(outputStream, gameStrategy->name, STRATEGY_LIST_NAME_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, STRATEGY_LIST_LOCATION_LAST_COLUMN_LENGTH);
}

void printGameStrategyTableList(OutputStream* outputStream) {
    int i;
    int size = strategies.size;
	printStrategyListHeader(outputStream);
    for (i = 0; i < size; i++) {
        GameStrategy* strategy = strategies.strategies[i];
        printGameStrategy(outputStream, strategy, i);
    }
	appendTableHeaderSeparatorLine(outputStream);
}
