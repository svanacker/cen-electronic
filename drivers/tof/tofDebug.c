#include "tofDebug.h"

#include <stdlib.h>

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#include "../../common/math/cenMath.h"

#include "tof.h"
#include "tofList.h"

#define TOF_SENSOR_INDEX_COLUMN_LENGTH		              10
#define TOF_SENSOR_ENABLE_COLUMN_LENGTH                    7
#define TOF_SENSOR_CHANGE_ADRESS_COLUMN_LENGTH             7
#define TOF_SENSOR_VALUE_THRESHOLD_COLUMN_LENGTH          10
#define TOF_SENSOR_VALUE_ORIENTATION_COLUMN_LENGTH        10

#define TOF_SENSOR_VALUE_DEC_COLUMN_LENGTH                10
#define TOF_SENSOR_VALUE_OBJECT_X_COLUMN_LENGTH           10
#define TOF_SENSOR_VALUE_OBJECT_Y_COLUMN_LENGTH           10

#define TOF_SENSOR_VALUE_HEX_COLUMN_LENGTH                10
#define TOF_SENSOR_LAST_COLUMN		                      10

/**
* Private.
*/
void printTofSensorDebugTableHeader(OutputStream* outputStream) {
    println(outputStream);
    appendTableHeaderSeparatorLine(outputStream);
    // First header line
    appendStringHeader(outputStream, "Index", TOF_SENSOR_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Enable", TOF_SENSOR_ENABLE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Change", TOF_SENSOR_CHANGE_ADRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Threshold", TOF_SENSOR_VALUE_THRESHOLD_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Orient.", TOF_SENSOR_VALUE_ORIENTATION_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Dist (mm)", TOF_SENSOR_VALUE_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Dist (mm)", TOF_SENSOR_VALUE_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Detected", TOF_SENSOR_VALUE_OBJECT_X_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Detected", TOF_SENSOR_VALUE_OBJECT_Y_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);
    // Second header line
    appendStringHeader(outputStream, "Index", TOF_SENSOR_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_ENABLE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Address", TOF_SENSOR_CHANGE_ADRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", TOF_SENSOR_VALUE_THRESHOLD_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(degree)", TOF_SENSOR_VALUE_ORIENTATION_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(Dec) mm", TOF_SENSOR_VALUE_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(Hex) mm", TOF_SENSOR_VALUE_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "X (mm)", TOF_SENSOR_VALUE_OBJECT_X_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Y (mm)", TOF_SENSOR_VALUE_OBJECT_Y_COLUMN_LENGTH);
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
