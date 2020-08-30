#include "locationDebug.h"

#include "location.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"
#include "../common/io/printTableWriter.h"

// USAGE TYPE

unsigned int appendLocationUsageTypeAsString(OutputStream* outputStream, enum LocationUsageType locationUsageType) {
    if (locationUsageType == LOCATION_USAGE_TYPE_PERMANENT) {
        return appendString(outputStream, "PERMANENT");
    } else if (locationUsageType == LOCATION_USAGE_TYPE_TEMPORARY) {
        return appendString(outputStream, "TEMPORARY");
    } else if (locationUsageType == LOCATION_USAGE_TYPE_TO_BE_REUSE) {
        return appendString(outputStream, "TO BE REUSE");
    } else if (locationUsageType == LOCATION_USAGE_TYPE_UNKNOWN) {
        return appendString(outputStream, "UNKNOWN");
    }
    return 0;
}

unsigned int appendLocationUsageTypeAsShortString(OutputStream* outputStream, enum LocationUsageType locationUsageType) {
    if (locationUsageType == LOCATION_USAGE_TYPE_PERMANENT) {
        return appendString(outputStream, "P");
    } else if (locationUsageType == LOCATION_USAGE_TYPE_TEMPORARY) {
        return appendString(outputStream, "T");
    } else if (locationUsageType == LOCATION_USAGE_TYPE_TO_BE_REUSE) {
        return appendString(outputStream, "R");
    } else if (locationUsageType == LOCATION_USAGE_TYPE_UNKNOWN) {
        return appendString(outputStream, "U");
    }
    return 0;
}

unsigned int addLocationUsageTypeTableData(OutputStream* outputStream, enum LocationUsageType locationUsageType, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendLocationUsageTypeAsString(outputStream, locationUsageType);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}

unsigned int addLocationUsageTypeShortTableData(OutputStream* outputStream, enum LocationUsageType locationUsageType, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendLocationUsageTypeAsShortString(outputStream, locationUsageType);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}

// ADJUST TYPE

unsigned int appendLocationAdjustTypeAsString(OutputStream* outputStream, enum LocationAdjustType locationAdjustType) {
    if (locationAdjustType == LOCATION_ADJUST_NONE) {
        return appendString(outputStream, "ADJUST NONE");
    }
    else if (locationAdjustType == LOCATION_ADJUST_X) {
        return appendString(outputStream, "ADJUST X");
    }
    else if (locationAdjustType == LOCATION_ADJUST_Y) {
        return appendString(outputStream, "ADJUST Y");
    }
    return 0;
}

unsigned int appendLocationAdjustTypeAsShortString(OutputStream* outputStream, enum LocationAdjustType locationAdjustType) {
    if (locationAdjustType == LOCATION_ADJUST_NONE) {
        return appendString(outputStream, "N");
    }
    else if (locationAdjustType == LOCATION_ADJUST_X) {
        return appendString(outputStream, "X");
    }
    else if (locationAdjustType == LOCATION_ADJUST_Y) {
        return appendString(outputStream, "Y");
    }
    return 0;
}

unsigned int addLocationAdjustTypeTableData(OutputStream* outputStream, enum LocationAdjustType locationAdjustType, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendLocationAdjustTypeAsString(outputStream, locationAdjustType);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}

unsigned int addLocationAdjustTypeShortTableData(OutputStream* outputStream, enum LocationAdjustType locationAdjustType, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendLocationAdjustTypeAsShortString(outputStream, locationAdjustType);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}
