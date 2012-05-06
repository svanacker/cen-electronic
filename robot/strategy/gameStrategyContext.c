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
	
	printPoint(outputStream, &(context->robotPosition), "");

	appendString(outputStream, "\n\tcurrentLocation=");
	if (context->nearestLocation != NULL) {
		printLocation(outputStream, context->nearestLocation);
	}
	else {
		appendString(outputStream, "NULL");

	}
	println(outputStream);
}
