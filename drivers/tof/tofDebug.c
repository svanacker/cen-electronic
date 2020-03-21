#include "tofDebug.h"

#include <stdlib.h>

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#include "tof.h"

// TYPE

unsigned int appendTofSensorTypeAsString(OutputStream* outputStream, enum TofSensorType tofSensorType) {
    if (tofSensorType == TOF_SENSOR_TYPE_UNKNOWN) {
        return appendString(outputStream, "UNKNOWN");
    } else if (tofSensorType == TOF_SENSOR_TYPE_PC) {
        return appendString(outputStream, "TOF PC");
    } else if (tofSensorType == TOF_SENSOR_TYPE_VL53L0X) {
        return appendString(outputStream, "VL53L0X");
    }
    return 0;
}

unsigned int addTofSensorTypeTableData(OutputStream* outputStream, enum TofSensorType tofSensorType, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendTofSensorTypeAsString(outputStream, tofSensorType);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}

// USAGE TYPE

unsigned int appendTofSensorUsageTypeAsString(OutputStream* outputStream, enum TofSensorUsageType tofSensorUsageType) {
    if (tofSensorUsageType == TOF_SENSOR_USAGE_TYPE_UNKNOWN) {
        return appendString(outputStream, "UNKNOWN");
    } else if (tofSensorUsageType == TOF_SENSOR_USAGE_TYPE_COLLISION) {
        return appendString(outputStream, "COLLISION");
    } else if (tofSensorUsageType == TOF_SENSOR_USAGE_TYPE_ACTION) {
        return appendString(outputStream, "ACTION");
    }
    return 0;
}

unsigned int appendTofSensorUsageTypeAsShortString(OutputStream* outputStream, enum TofSensorUsageType tofSensorUsageType) {
    if (tofSensorUsageType == TOF_SENSOR_USAGE_TYPE_UNKNOWN) {
        return appendString(outputStream, "U");
    } else if (tofSensorUsageType == TOF_SENSOR_USAGE_TYPE_COLLISION) {
        return appendString(outputStream, "C");
    } else if (tofSensorUsageType == TOF_SENSOR_USAGE_TYPE_ACTION) {
        return appendString(outputStream, "A");
    }
    return 0;
}

unsigned int addTofSensorUsageTypeTableData(OutputStream* outputStream, enum TofSensorUsageType tofSensorUsageType, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendTofSensorUsageTypeAsString(outputStream, tofSensorUsageType);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}

unsigned int addTofSensorUsageTypeShortTableData(OutputStream* outputStream, enum TofSensorUsageType tofSensorUsageType, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendTofSensorUsageTypeAsShortString(outputStream, tofSensorUsageType);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}


// START RESULT TYPE

unsigned int appendTofSensorStartResultAsString(OutputStream* outputStream, enum TofSensorStartResult tofSensorStartResult) {
    if (tofSensorStartResult == TOF_SENSOR_START_RESULT_UNKNOWN) {
        return appendString(outputStream, "UNKNOWN");
    } else if (tofSensorStartResult == TOF_SENSOR_START_RESULT_DISABLED) {
        return appendString(outputStream, "DISABLED");
    } else if (tofSensorStartResult == TOF_SENSOR_START_RESULT_OK) {
        return appendString(outputStream, "OK");
    } else if (tofSensorStartResult == TOF_SENSOR_START_RESULT_ALREADY_STARTED) {
        return appendString(outputStream, "ALREADY STARTED");
    } else if (tofSensorStartResult == TOF_SENSOR_START_RESULT_INIT_PROBLEM) {
        return appendString(outputStream, "INIT PROBLEM");
    } else if (tofSensorStartResult == TOF_SENSOR_START_RESULT_CHANGE_ADDRESS_PROBLEM) {
        return appendString(outputStream, "CHANGE ADDR PROB.");
    }
    return 0;
}

unsigned int appendTofSensorStartResultAsShortString(OutputStream* outputStream, enum TofSensorStartResult tofSensorStartResult) {
    if (tofSensorStartResult == TOF_SENSOR_START_RESULT_UNKNOWN) {
        return appendString(outputStream, "?");
    } else if (tofSensorStartResult == TOF_SENSOR_START_RESULT_DISABLED) {
        return appendString(outputStream, "_");
    } else if (tofSensorStartResult == TOF_SENSOR_START_RESULT_OK) {
        return appendString(outputStream, "[");
    } else if (tofSensorStartResult == TOF_SENSOR_START_RESULT_ALREADY_STARTED) {
        return appendString(outputStream, "S");
    } else if (tofSensorStartResult == TOF_SENSOR_START_RESULT_INIT_PROBLEM) {
        return appendString(outputStream, "X");
    } else if (tofSensorStartResult == TOF_SENSOR_START_RESULT_CHANGE_ADDRESS_PROBLEM) {
        return appendString(outputStream, "A");
    }
    return 0;
}

unsigned int appendTofSensorStartResultTableData(OutputStream* outputStream, enum TofSensorStartResult tofSensorStartResult, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendTofSensorStartResultAsString(outputStream, tofSensorStartResult);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}

unsigned int appendTofSensorStartResultShortTableData(OutputStream* outputStream, enum TofSensorStartResult tofSensorStartResult, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendTofSensorStartResultAsShortString(outputStream, tofSensorStartResult);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}

