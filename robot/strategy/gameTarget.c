#include <stdlib.h>

#include "gameTarget.h"

#include "gameTargetActionList.h"

#include "../../common/commons.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void clearGameTarget(GameTarget* target) {
	target->name = "?";
	target->gain = 0;
	target->available = FALSE;
	
	if (&(target->actionList) != NULL) {
		clearTargetActionList(&(target->actionList));
	}
}

void printGameTarget(OutputStream* outputStream, GameTarget* target, BOOL includeItems) {
	appendString(outputStream, "target:");
	appendKeyAndName(outputStream, "name=", target->name);
	appendStringAndDecf(outputStream, ", gain=", target->gain);
	appendStringAndDec(outputStream, ", available=", target->available);
	// TODO : Point
	println(outputStream);
	
	if (includeItems) {
		printGameTargetActionList(outputStream, &(target->actionList));
	}
}
