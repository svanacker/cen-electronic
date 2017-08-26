#include "motionParameterType.h"

#include "../../common/math/cenMath.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

enum MotionParameterType getMotionParameterType(float left, float right) {
    if (floatEqualsZero(left) && floatEqualsZero(right)) {
        return MOTION_PARAMETER_TYPE_MAINTAIN_POSITION;
    } else if (left <= 0.0f && right >= 0.0f) {
        return MOTION_PARAMETER_TYPE_ROTATION;
    } else if (left >= 0.0f && right <= 0.0f) {
        return MOTION_PARAMETER_TYPE_ROTATION;
    } else {
        return MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD;
    }
}

unsigned char appendMotionParameterTypeAsString(OutputStream* outputStream, enum MotionParameterType motionParameterType) {
    if (motionParameterType == MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD) {
        return appendString(outputStream, "FOR-BACK WARD");
    }
    else if (motionParameterType == MOTION_PARAMETER_TYPE_ROTATION) {
        return appendString(outputStream, "ROTATION");
    }
    else if (motionParameterType == MOTION_PARAMETER_TYPE_ROTATION_ONE_WHEEL) {
        return appendString(outputStream, "ROT_ONE_WHEEL");
    }
    else if (motionParameterType == MOTION_PARAMETER_TYPE_MAINTAIN_POSITION) {
        return appendString(outputStream, "MAINTAIN_POS");
    }
    else {
        append(outputStream, '?');
		return 1;
    }
    return 0;
}

unsigned int addMotionParameterTypeTableData(OutputStream* outputStream, enum MotionParameterType motionParameterType, int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	unsigned int length = appendMotionParameterTypeAsString(outputStream, motionParameterType);
	return length + appendSpaces(outputStream, columnSize - length) + 2;
}