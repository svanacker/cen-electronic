#include "locationDebug.h"

#include "location.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"
#include "../common/io/printTableWriter.h"

// USAGE TYPE

unsigned int appendLocationUsageTypeAsString(OutputStream* outputStream, enum LocationUsageType LocationUsageType) {
    if (LocationUsageType == LOCATION_USAGE_TYPE_PERMANENT) {
        return appendString(outputStream, "PERMANENT");
    }
    else if (LocationUsageType == LOCATION_USAGE_TYPE_TEMPORARY) {
        return appendString(outputStream, "TEMPORARY");
    }
    else if (LocationUsageType == LOCATION_USAGE_TYPE_TO_BE_REUSE) {
        return appendString(outputStream, "TO BE REUSE");
    }
    else if (LocationUsageType == LOCATION_USAGE_TYPE_UNKNOWN) {
        return appendString(outputStream, "UNKNOWN");
    }
    return 0;
}

unsigned int appendLocationUsageTypeAsShortString(OutputStream* outputStream, enum LocationUsageType LocationUsageType) {
    if (LocationUsageType == LOCATION_USAGE_TYPE_PERMANENT) {
        return appendString(outputStream, "P");
    }
    else if (LocationUsageType == LOCATION_USAGE_TYPE_TEMPORARY) {
        return appendString(outputStream, "T");
    }
    else if (LocationUsageType == LOCATION_USAGE_TYPE_TO_BE_REUSE) {
        return appendString(outputStream, "R");
    }
    else if (LocationUsageType == LOCATION_USAGE_TYPE_UNKNOWN) {
        return appendString(outputStream, "U");
    }
    return 0;
}

unsigned int addLocationUsageTypeTableData(OutputStream* outputStream, enum LocationUsageType LocationUsageType, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendLocationUsageTypeAsString(outputStream, LocationUsageType);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}

unsigned int addLocationUsageTypeShortTableData(OutputStream* outputStream, enum LocationUsageType LocationUsageType, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendLocationUsageTypeAsShortString(outputStream, LocationUsageType);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}
