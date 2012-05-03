#include "gameStrategy.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void printGameStrategy(OutputStream* outputStream, GameStrategy* strategy) {
	appendKeyAndName(outputStream, "strategy.name=", strategy->name);
	println(outputStream);
}
