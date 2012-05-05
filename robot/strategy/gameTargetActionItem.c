#include "gameTargetActionItem.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void printGameTargetActionItem(OutputStream* outputStream, GameTargetActionItem* targetActionItem) {
	appendString(outputStream, "\t\tactionItem:");
	appendKeyAndName(outputStream, "name=", targetActionItem->name);
	println(outputStream);
}
