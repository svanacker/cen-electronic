#include <stdlib.h>

#include "gameStrategyContext.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void printGameStrategyContext(OutputStream* outputStream, GameStrategyContext* context) {
	appendString(outputStream, "GameStrategyContext\n");
	appendString(outputStream, "\tstrategy.name=");

	// gameStrategy
	if (context->gameStrategy != NULL) {
		appendString(outputStream, context->gameStrategy->name);
	}
	else {
		appendString(outputStream, "NULL");
	}

	// elapsedMatchTime
	appendStringAndDecf(outputStream, "\n\telapsedMatchTime=", context->elapsedMatchTime);
	println(outputStream);
	
	// Point
	appendString(outputStream, "\t");
	printPoint(outputStream, &(context->robotPosition), "");

	// current location
	appendString(outputStream, "\tcurrentLocation=");
	if (context->nearestLocation != NULL) {
		printLocation(outputStream, context->nearestLocation);
	}
	else {
		appendString(outputStream, "NULL");
	}

	appendString(outputStream, "\n\tcurrentTarget=");
	if (context->currentTarget != NULL) {
		printGameTarget(outputStream, context->currentTarget, FALSE);
	}
	else {
		appendString(outputStream, "NULL");
	}


	println(outputStream);
}
