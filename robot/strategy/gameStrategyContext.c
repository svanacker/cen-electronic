#include <stdlib.h>

#include "gameStrategyContext.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void printGameStrategyContext(OutputStream* outputStream, GameStrategyContext* context) {
	appendString(outputStream, "GameStrategyContext\n");
	appendString(outputStream, "\tstrategy.name=");

	if (context->gameStrategy != NULL) {
		appendString(outputStream, context->gameStrategy->name);
	}
	else {
		appendString(outputStream, "NULL");
	}
	appendStringAndDecf(outputStream, "\n\telapsedMatchTime=", context->elapsedMatchTime);
	appendString(outputStream, "\n\tcurrentLocation=");
	if (context->currentLocation != NULL) {
		printLocation(outputStream, context->currentLocation);
	}
	else {
		appendString(outputStream, "NULL");

	}
	println(outputStream);
}
