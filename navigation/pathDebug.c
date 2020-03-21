#include "pathDebug.h"

#include "path.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"
#include "../common/io/printTableWriter.h"

// USAGE TYPE

unsigned int appendPathDataUsageTypeAsString(OutputStream* outputStream, enum PathDataUsageType pathDataUsageType) {
    if (pathDataUsageType == PATH_DATA_USAGE_TYPE_PERMANENT) {
        return appendString(outputStream, "PERMANENT");
    } else if (pathDataUsageType == PATH_DATA_USAGE_TYPE_TEMPORARY) {
        return appendString(outputStream, "TEMPORARY");
    } else if (pathDataUsageType == PATH_DATA_USAGE_TYPE_TO_BE_REUSE) {
        return appendString(outputStream, "TO BE REUSE");
    } else if (pathDataUsageType == PATH_DATA_USAGE_TYPE_UNKNOWN) {
        return appendString(outputStream, "UNKNOWN");
    }
    return 0;
}

unsigned int appendPathDataUsageTypeAsShortString(OutputStream* outputStream, enum PathDataUsageType pathDataUsageType) {
    if (pathDataUsageType == PATH_DATA_USAGE_TYPE_PERMANENT) {
        return appendString(outputStream, "P");
    } else if (pathDataUsageType == PATH_DATA_USAGE_TYPE_TEMPORARY) {
        return appendString(outputStream, "T");
    } else if (pathDataUsageType == PATH_DATA_USAGE_TYPE_TO_BE_REUSE) {
        return appendString(outputStream, "R");
    } else if (pathDataUsageType == PATH_DATA_USAGE_TYPE_UNKNOWN) {
        return appendString(outputStream, "U");
    }
    return 0;
}

unsigned int addPathDataUsageTypeTableData(OutputStream* outputStream, enum PathDataUsageType pathDataUsageType, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendPathDataUsageTypeAsString(outputStream, pathDataUsageType);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}

unsigned int addPathDataUsageTypeShortTableData(OutputStream* outputStream, enum PathDataUsageType pathDataUsageType, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendPathDataUsageTypeAsShortString(outputStream, pathDataUsageType);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}
