#include "pidMotionDefinitionState.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

unsigned int appendMotionDefinitionStateString(OutputStream* outputStream, enum PidMotionDefinitionState state) {
    if (state == PID_MOTION_DEFINITION_STATE_UNDEFINED) {
        return appendString(outputStream, "UNDEFINED");
    }
    else if (state == PID_MOTION_DEFINITION_STATE_SET) {
		return appendString(outputStream, "SET");
    }
    else if (state == PID_MOTION_DEFINITION_STATE_ACTIVE) {
		return appendString(outputStream, "ACTIVE");
    }
    else if (state == PID_MOTION_DEFINITION_STATE_ENDED) {
		return appendString(outputStream, "ENDED");
    }
    else {
		append(outputStream, '?');
		return 1;
    }
	return 0;
}

unsigned int addPidMotionDefinitionStateTableData(OutputStream* outputStream, enum PidMotionDefinitionState state, int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	unsigned int length = appendMotionDefinitionStateString(outputStream, state);
	return length + appendSpaces(outputStream, columnSize - length) + 2;
}
