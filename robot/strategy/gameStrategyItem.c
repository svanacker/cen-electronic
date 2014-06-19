#include "gameStrategyItem.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void printGameStrategyItem(OutputStream* outputStream, GameStrategyItem* strategyItem) {
    appendKeyAndName(outputStream, "\tstrategyItem->target->name=", strategyItem->target->name);
    println(outputStream);
}
