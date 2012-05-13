#include <stdlib.h>

#include "gameStrategyContext.h"

#include "../../navigation/locationList.h"

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
	
	// Robot Position
	appendString(outputStream, "\trobotPosition=");
	printPoint(outputStream, &(context->robotPosition), "");

	// nearestLocation
	appendString(outputStream, "\tnearestLocation=");
	if (context->nearestLocation != NULL) {
		printLocation(outputStream, context->nearestLocation);
	}
	else {
		appendString(outputStream, "NULL");
	}

	// Robot Position
	appendString(outputStream, "\n\topponentRobotPosition=");
	printPoint(outputStream, &(context->opponentRobotPosition), "");

	// current Target
	appendString(outputStream, "\n\tcurrentTarget=");
	if (context->currentTarget != NULL) {
		printGameTarget(outputStream, context->currentTarget, FALSE);
	}
	else {
		appendString(outputStream, "NULL");
	}

	// currentTrajectory
	if (&(context->currentTrajectory) != NULL) {
		printLocationList(outputStream, "\n\tcurrentTrajectory:", &(context->currentTrajectory));
	}
	else {
		appendString(outputStream, "\n\tcurrentTrajectory=NULL");
	}
	println(outputStream);
}
