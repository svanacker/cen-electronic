#include "gameTarget.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void printGameTarget(OutputStream* outputStream, GameTarget* target) {
	appendKeyAndName(outputStream, "target.name=", target->name);
	appendStringAndDecf(outputStream, "target.gain=", target->gain);
	appendStringAndDec(outputStream, "target.available=", target->available);
	// TODO : Point
	println(outputStream);
}
