#include "motionParameterType.h"

#include "../../common/math/cenMath.h"

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
