#include "pidType.h"

#include <stdbool.h>

#include "../../common/error/error.h"

#include "../../motion/pid/instructionType.h"
#include "../../motion/parameters/motionParameterType.h"

// STANDARD ENUM MANAGEMENT

bool checkPidTypeIndexInRange(unsigned int pidTypeIndex) {
    return (pidTypeIndex >= 0 || pidTypeIndex < PID_TYPE_COUNT);
}

unsigned int getPidTypeCount(void) {
    return PID_TYPE_COUNT;
}

unsigned int pidTypeEnumToIndex(enum PidType pidType) {
    return (unsigned int) pidType;
}

enum PidType pidTypeValueOf(unsigned int pidTypeIndex) {
    if (!checkPidTypeIndexInRange(pidTypeIndex)) {
        writeError(PID_TYPE_UNKNOWN_ENUM);
        return PID_TYPE_NONE;
    }
    return (enum PidType) pidTypeIndex;
}

// PID TYPE SPECIFIC

enum PidType getPidType(enum MotionParameterType motionParameterType, enum InstructionType instructionType) {
    if (motionParameterType == MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD) {
        if (instructionType == THETA) {
            return PID_TYPE_GO_INDEX;
        }
        // For Alpha, we maintain
        return PID_TYPE_MAINTAIN_POSITION_INDEX;
    } else if (motionParameterType == MOTION_PARAMETER_TYPE_ROTATION) {
        if (instructionType == ALPHA) {
            return PID_TYPE_ROTATE_INDEX;
        }
        // For Theta, we maintain
        return PID_TYPE_MAINTAIN_POSITION_INDEX;
    } else if (motionParameterType == MOTION_PARAMETER_TYPE_MAINTAIN_POSITION) {
        // For both Theta / Alpha Maintain
        return PID_TYPE_MAINTAIN_POSITION_INDEX;
    }
    // Default value, must not enter here
    return PID_TYPE_NONE;
}

