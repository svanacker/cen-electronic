#include "profileType.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void appendProfileTypeAsString(enum ProfileType profileType, OutputStream* outputStream) {
    if (profileType == PROFILE_TYPE_TRIANGLE) {
        appendString(outputStream, "TRIANGLE");
    }
    else if (profileType == PROFILE_TYPE_TRAPEZE) {
        appendString(outputStream, "TRAPEZE");
    }
    else {
        append(outputStream, '?');
    }
}