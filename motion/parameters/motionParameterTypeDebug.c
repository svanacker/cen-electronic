#include "motionParameterTypeDebug.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

unsigned char appendMotionParameterTypeAsString(OutputStream* outputStream, enum MotionParameterType motionParameterType) {
    if (motionParameterType == MOTION_PARAMETER_TYPE_UNDEFINED) {
        return appendString(outputStream, "UNDEFINED");
    } else if (motionParameterType == MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD) {
        return appendString(outputStream, "FORWARD-BACKWARD");
    } else if (motionParameterType == MOTION_PARAMETER_TYPE_ROTATION) {
        return appendString(outputStream, "ROTATION");
    } else if (motionParameterType == MOTION_PARAMETER_TYPE_ROTATION_ONE_WHEEL) {
        return appendString(outputStream, "ROTATION_ONE_WHEEL");
    } else if (motionParameterType == MOTION_PARAMETER_TYPE_MAINTAIN_POSITION) {
        return appendString(outputStream, "MAINTAIN_POSITION");
    } else {
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