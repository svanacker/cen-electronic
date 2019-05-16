#include "tofDebug.h"

#include <stdlib.h>

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#include "../../common/math/cenMath.h"

#include "tof.h"
#include "tofList.h"

#define TOF_SENSOR_INDEX_COLUMN_LENGTH		              4
#define TOF_SENSOR_NAME_COLUMN_LENGTH		              13
#define TOF_SENSOR_TYPE_COLUMN_LENGTH		              5
#define TOF_SENSOR_ENABLE_COLUMN_LENGTH                    7
#define TOF_SENSOR_CHANGE_ADRESS_COLUMN_LENGTH             7
#define TOF_SENSOR_VALUE_THRESHOLD_COLUMN_LENGTH          10
#define TOF_SENSOR_VALUE_ORIENTATION_COLUMN_LENGTH         9

#define TOF_SENSOR_VALUE_DEC_COLUMN_LENGTH                8
#define TOF_SENSOR_VALUE_HEX_COLUMN_LENGTH                8

#define TOF_SENSOR_VALUE_OBJECT_X_COLUMN_LENGTH           9
#define TOF_SENSOR_VALUE_OBJECT_Y_COLUMN_LENGTH           9

#define TOF_SENSOR_LAST_COLUMN		                      1

// SERVO TYPE

unsigned int appendTofSensorTypeAsString(OutputStream* outputStream, enum TofSensorType tofSensorType) {
    if (tofSensorType == TOF_SENSOR_TYPE_UNKNOWN) {
        return appendString(outputStream, "UNKNOWN");
    }
    else if (tofSensorType == TOF_SENSOR_TYPE_COLLISION) {
        return appendString(outputStream, "COLLISION");
    }
    else if (tofSensorType == TOF_SENSOR_TYPE_ACTION) {
        return appendString(outputStream, "ACTION");
    }
	return 0;
}

unsigned int appendTofSensorTypeAsShortString(OutputStream* outputStream, enum TofSensorType tofSensorType) {
    if (tofSensorType == TOF_SENSOR_TYPE_UNKNOWN) {
        return appendString(outputStream, "U");
    }
    else if (tofSensorType == TOF_SENSOR_TYPE_COLLISION) {
        return appendString(outputStream, "C");
    }
    else if (tofSensorType == TOF_SENSOR_TYPE_ACTION) {
        return appendString(outputStream, "A");
    }
	return 0;
}

unsigned int addTofSensorTypeTableData(OutputStream* outputStream, enum TofSensorType tofSensorType, int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	unsigned int length = appendTofSensorTypeAsString(outputStream, tofSensorType);
	return length + appendSpaces(outputStream, columnSize - length) + 2;
}

unsigned int addTofSensorTypeShortTableData(OutputStream* outputStream, enum TofSensorType tofSensorType, int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	unsigned int length = appendTofSensorTypeAsShortString(outputStream, tofSensorType);
	return length + appendSpaces(outputStream, columnSize - length) + 2;
}

/**
* Private.
*/
void printTofSensorDebugTableHeader(OutputStream* outputStream) {
    println(outputStream);
    appendTableHeaderSeparatorLine(outputStream);
    // First header line
    appendStringHeader(outputStream, "Idx", TOF_SENSOR_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Name", TOF_SENSOR_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Type", TOF_SENSOR_TYPE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Enable", TOF_SENSOR_ENABLE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Change", TOF_SENSOR_CHANGE_ADRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Threshold", TOF_SENSOR_VALUE_THRESHOLD_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Orient.", TOF_SENSOR_VALUE_ORIENTATION_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Dist", TOF_SENSOR_VALUE_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Dist", TOF_SENSOR_VALUE_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Detected", TOF_SENSOR_VALUE_OBJECT_X_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Detected", TOF_SENSOR_VALUE_OBJECT_Y_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);
    
    // Second header line
    appendStringHeader(outputStream, "", TOF_SENSOR_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_TYPE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_ENABLE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Address", TOF_SENSOR_CHANGE_ADRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", TOF_SENSOR_VALUE_THRESHOLD_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(degree)", TOF_SENSOR_VALUE_ORIENTATION_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(Dec)", TOF_SENSOR_VALUE_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(Hex)", TOF_SENSOR_VALUE_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "X", TOF_SENSOR_VALUE_OBJECT_X_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Y", TOF_SENSOR_VALUE_OBJECT_Y_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);
    
    // Third header line
    appendStringHeader(outputStream, "", TOF_SENSOR_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_TYPE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_ENABLE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_CHANGE_ADRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_VALUE_THRESHOLD_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_VALUE_ORIENTATION_COLUMN_LENGTH);
    appendStringHeader(outputStream, "mm", TOF_SENSOR_VALUE_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "mm", TOF_SENSOR_VALUE_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", TOF_SENSOR_VALUE_OBJECT_X_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", TOF_SENSOR_VALUE_OBJECT_Y_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);
    
    appendTableHeaderSeparatorLine(outputStream);
}

void printTofSensorTable(OutputStream* outputStream, TofSensorList* tofSensorList, Point* pointOfView, float pointOfViewAngleRadian) {
    printTofSensorDebugTableHeader(outputStream);
    unsigned int index;
    for (index = 0; index < tofSensorList->size; index++) {
        // TOF Configuration
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, index);
        unsigned int distance = tofSensor->tofGetDistanceMM(tofSensor);

        appendDecTableData(outputStream, index, TOF_SENSOR_INDEX_COLUMN_LENGTH);
        appendStringTableData(outputStream, tofSensor->name, TOF_SENSOR_NAME_COLUMN_LENGTH);
        addTofSensorTypeShortTableData(outputStream, tofSensor->type, TOF_SENSOR_TYPE_COLUMN_LENGTH);
        appendBoolAsStringTableData(outputStream, tofSensor->enabled, TOF_SENSOR_ENABLE_COLUMN_LENGTH);
        appendBoolAsStringTableData(outputStream, tofSensor->changeAddress, TOF_SENSOR_CHANGE_ADRESS_COLUMN_LENGTH);
        appendDecTableData(outputStream, tofSensor->thresholdDistanceMM, TOF_SENSOR_VALUE_THRESHOLD_COLUMN_LENGTH);
        appendDecfTableData(outputStream, radToDeg(tofSensor->orientationRadian), TOF_SENSOR_VALUE_ORIENTATION_COLUMN_LENGTH);
        
        // Distance
        appendDecTableData(outputStream, distance, TOF_SENSOR_VALUE_DEC_COLUMN_LENGTH);
        appendHex4TableData(outputStream, distance, TOF_SENSOR_VALUE_HEX_COLUMN_LENGTH);
        
        // DetectedPoint if any
        Point detectedPoint;
        bool detected = tofComputeDetectedPointIfAny(tofSensor, pointOfView, pointOfViewAngleRadian, &detectedPoint);
        // Distance to the point of View only if in the Threshold
        if (detected) {
            appendDecfTableData(outputStream, detectedPoint.x, TOF_SENSOR_VALUE_OBJECT_X_COLUMN_LENGTH);        
            appendDecfTableData(outputStream, detectedPoint.y, TOF_SENSOR_VALUE_OBJECT_Y_COLUMN_LENGTH);
        }
        else {
            appendStringTableData(outputStream, "-", TOF_SENSOR_VALUE_OBJECT_X_COLUMN_LENGTH);        
            appendStringTableData(outputStream, "-", TOF_SENSOR_VALUE_OBJECT_Y_COLUMN_LENGTH);        
        }
        appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);
    }

    appendTableHeaderSeparatorLine(outputStream);
}
