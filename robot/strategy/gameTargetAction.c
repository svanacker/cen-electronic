#include "gameTargetAction.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void printGameTargetAction(OutputStream* outputStream, GameTargetAction* targetAction) {
	appendString(outputStream, "\taction:");
	appendKeyAndName(outputStream, "startLocation=", targetAction->startLocation->name);
	appendKeyAndName(outputStream, ", end=", targetAction->endLocation->name);
	appendStringAndDec(outputStream, ", timeToAchieve=", targetAction->timeToAchieve);
	println(outputStream);
}
