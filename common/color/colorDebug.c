#include "colorDebug.h"

#include "color.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void printColorType(OutputStream* outputStream, enum ColorType colorType) {
	if (colorType == COLOR_TYPE_UNKNOWN) {
		appendString(outputStream, "UNKNOWN");
	}
	else if (colorType == COLOR_TYPE_RED) {
		appendString(outputStream, "RED");
	}
	else if (colorType == COLOR_TYPE_GREEN) {
		appendString(outputStream, "GREEN");
	}
	else if (colorType == COLOR_TYPE_ORANGE) {
		appendString(outputStream, "ORANGE");
	}
	else if (colorType == COLOR_TYPE_BLUE) {
		appendString(outputStream, "BLUE");
	}
}