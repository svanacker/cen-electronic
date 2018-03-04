#include "gameStrategy.h"
#include "gameStrategyItem.h"
#include "gameTarget.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

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
