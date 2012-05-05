#include "gameTargetAction.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void printGameTargetAction(OutputStream* outputStream, GameTargetAction* targetAction) {
	appendKeyAndName(outputStream, "target.startLocation=", targetAction->startLocation->name);
	appendKeyAndName(outputStream, "target.endLocation=", targetAction->endLocation->name);
	appendStringAndDec(outputStream, "target.timeToAchieve=", targetAction->timeToAchieve);
}
