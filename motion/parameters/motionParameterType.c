#include "motionParameterType.h"

#include "../../common/math/cenMath.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

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

void appendMotionParameterTypeAsString(enum MotionParameterType motionParameterType, OutputStream* outputStream) {
    if (motionParameterType == MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD) {
        appendString(outputStream, "FORWARD_OR_BACKWARD");
    }
    else if (motionParameterType == MOTION_PARAMETER_TYPE_ROTATION) {
        appendString(outputStream, "ROTATION");
    }
    else if (motionParameterType == MOTION_PARAMETER_TYPE_ROTATION_ONE_WHEEL) {
        appendString(outputStream, "ROTATION_ONE_WHEEL");
    }
    else if (motionParameterType == MOTION_PARAMETER_TYPE_MAINTAIN_POSITION) {
        appendString(outputStream, "MAINTAIN_POSITION");
    }
    else {
        append(outputStream, '?');
    }
}