#include "profileType.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"

unsigned int appendProfileTypeAsString(OutputStream* outputStream, enum ProfileType profileType) {
    if (profileType == PROFILE_TYPE_UNDEFINED) {
        return appendString(outputStream, "UNDEFINED");
    } else if (profileType == PROFILE_TYPE_TRIANGLE) {
        return appendString(outputStream, "TRIANGLE");
    } else if (profileType == PROFILE_TYPE_TRAPEZE) {
        return appendString(outputStream, "TRAPEZE");
    } else {
        append(outputStream, '?');
        return 1;
    }
    return 0;
}

unsigned int addMotionProfileTypeTableData(OutputStream* outputStream, enum ProfileType profileType, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendProfileTypeAsString(outputStream, profileType);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}