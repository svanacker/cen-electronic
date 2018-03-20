#include "detectedMotionType.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

unsigned int appendDetectedMotionTypeAsString(OutputStream* outputStream, enum DetectedMotionType detectedMotionType) {
	if (detectedMotionType == DETECTED_MOTION_TYPE_NO_POSITION_TO_REACH) {
		return appendString(outputStream, "NO_POSITION_TO_REACH");
	}
	else if (detectedMotionType == DETECTED_MOTION_TYPE_POSITION_TO_MAINTAIN) {
		return appendString(outputStream, "POSITION_TO_MAINTAIN");
	}
	else if (detectedMotionType == DETECTED_MOTION_TYPE_POSITION_IN_PROGRESS) {
		return appendString(outputStream, "POSITION_IN_PROGRESS");
	}
	else if (detectedMotionType == DETECTED_MOTION_TYPE_POSITION_REACHED) {
		return appendString(outputStream, "POSITION_REACHED");
	}
    else if (detectedMotionType == DETECTED_MOTION_TYPE_POSITION_SHOCK_WHEELS) {
        return appendString(outputStream, "SHOCK_WHEELS");
    }
	else if (detectedMotionType == DETECTED_MOTION_TYPE_POSITION_BLOCKED_WHEELS) {
		return appendString(outputStream, "BLOCKED_WHEELS");
	}
	else if (detectedMotionType == DETECTED_MOTION_TYPE_POSITION_OBSTACLE) {
		return appendString(outputStream, "OBSTACLE");
	}
	else {
		append(outputStream, '?');
		return 1;
	}
	return 0;
}

unsigned int addDetectedMotionTypeTableData(OutputStream* outputStream, enum DetectedMotionType detectedMotionType, unsigned int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	unsigned int length = appendDetectedMotionTypeAsString(outputStream, detectedMotionType);
	return length + appendSpaces(outputStream, columnSize - length) + 2;
}