#include "gameTarget.h"

#include "gameTargetActionList.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void printGameTarget(OutputStream* outputStream, GameTarget* target) {
	appendString(outputStream, "target:");
	appendKeyAndName(outputStream, "name=", target->name);
	appendStringAndDecf(outputStream, ", gain=", target->gain);
	appendStringAndDec(outputStream, ", available=", target->available);
	// TODO : Point
	println(outputStream);
	
	printGameTargetActionList(outputStream, &(target->actionList));
}
