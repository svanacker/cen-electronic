#include "tofListDebug.h"

#include <stdlib.h>

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#include "../../common/math/cenMath.h"

#include "tof.h"
#include "tofDetectionUtils.h"
#include "tofDebug.h"
#include "tofList.h"

// ------------------------------------------------------ CONFIG ------------------------------------------

/**
* Private.
*/
void printTofSensorConfigDebugTableHeader(OutputStream* outputStream) {
    println(outputStream);
    appendTableHeaderSeparatorLine(outputStream);
    // First header line
    appendStringHeader(outputStream, "Id", TOF_SENSOR_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Name", TOF_SENSOR_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Type", TOF_SENSOR_TYPE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Usage", TOF_SENSOR_USAGE_TYPE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Start", TOF_SENSOR_START_RESULT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Enab.", TOF_SENSOR_ENABLE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Thres", TOF_SENSOR_VALUE_THRESHOLD_MAX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Thres", TOF_SENSOR_VALUE_THRESHOLD_MIN_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Detect.", TOF_SENSOR_VALUE_DETECTION_THRESHOLD_COUNT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Beam", TOF_SENSOR_VALUE_BEAM_ANGLE_DEGREE_LENGTH);
    appendStringHeader(outputStream, "Orien", TOF_SENSOR_VALUE_ORIENTATION_ANGLE_DEGREE_LENGTH);
    appendStringHeader(outputStream, "Dist.", TOF_SENSOR_VALUE_DISTANCE_FROM_ROBOT_CENTER_MM_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Angle.", TOF_SENSOR_VALUE_ANGLE_FROM_ROBOT_CENTER_DEGREE_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);
    
    // Second header line
    appendStringHeader(outputStream, "", TOF_SENSOR_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_TYPE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Type", TOF_SENSOR_USAGE_TYPE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Result", TOF_SENSOR_START_RESULT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_ENABLE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Hold", TOF_SENSOR_VALUE_THRESHOLD_MAX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Hold", TOF_SENSOR_VALUE_THRESHOLD_MIN_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Thres.", TOF_SENSOR_VALUE_DETECTION_THRESHOLD_COUNT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Angle", TOF_SENSOR_VALUE_BEAM_ANGLE_DEGREE_LENGTH);
    appendStringHeader(outputStream, "Angle", TOF_SENSOR_VALUE_ORIENTATION_ANGLE_DEGREE_LENGTH);
    appendStringHeader(outputStream, "Robot.", TOF_SENSOR_VALUE_DISTANCE_FROM_ROBOT_CENTER_MM_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Robot.", TOF_SENSOR_VALUE_ANGLE_FROM_ROBOT_CENTER_DEGREE_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);

    // Third header line
    appendStringHeader(outputStream, "", TOF_SENSOR_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_TYPE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_USAGE_TYPE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_START_RESULT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_ENABLE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Max", TOF_SENSOR_VALUE_THRESHOLD_MAX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Min", TOF_SENSOR_VALUE_THRESHOLD_MIN_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Count", TOF_SENSOR_VALUE_DETECTION_THRESHOLD_COUNT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(Deg)", TOF_SENSOR_VALUE_BEAM_ANGLE_DEGREE_LENGTH);
    appendStringHeader(outputStream, "(Deg)", TOF_SENSOR_VALUE_ORIENTATION_ANGLE_DEGREE_LENGTH);
    appendStringHeader(outputStream, "Center", TOF_SENSOR_VALUE_DISTANCE_FROM_ROBOT_CENTER_MM_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Center", TOF_SENSOR_VALUE_ANGLE_FROM_ROBOT_CENTER_DEGREE_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);

    // 4th header line
    appendStringHeader(outputStream, "", TOF_SENSOR_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_TYPE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_USAGE_TYPE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_START_RESULT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_ENABLE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", TOF_SENSOR_VALUE_THRESHOLD_MAX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", TOF_SENSOR_VALUE_THRESHOLD_MIN_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_VALUE_DETECTION_THRESHOLD_COUNT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_VALUE_BEAM_ANGLE_DEGREE_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_VALUE_ORIENTATION_ANGLE_DEGREE_LENGTH);
    appendStringHeader(outputStream, "(mm)", TOF_SENSOR_VALUE_DISTANCE_FROM_ROBOT_CENTER_MM_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", TOF_SENSOR_VALUE_ANGLE_FROM_ROBOT_CENTER_DEGREE_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);

    appendTableHeaderSeparatorLine(outputStream);
}

void printTofSensorConfigTable(OutputStream* outputStream, TofSensorList* tofSensorList) {
    printTofSensorConfigDebugTableHeader(outputStream);
    unsigned int index;
    for (index = 0; index < tofSensorList->size; index++) {
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, index);

        appendDecTableData(outputStream, index, TOF_SENSOR_INDEX_COLUMN_LENGTH);
        appendStringTableData(outputStream, tofSensor->name, TOF_SENSOR_NAME_COLUMN_LENGTH);
        addTofSensorTypeTableData(outputStream, tofSensor->type, TOF_SENSOR_TYPE_COLUMN_LENGTH);
        addTofSensorUsageTypeShortTableData(outputStream, tofSensor->usageType, TOF_SENSOR_USAGE_TYPE_COLUMN_LENGTH);
        appendTofSensorStartResultShortTableData(outputStream, tofSensor->startResult, TOF_SENSOR_START_RESULT_COLUMN_LENGTH);
        appendBoolAsStringTableData(outputStream, tofSensor->enabled, TOF_SENSOR_ENABLE_COLUMN_LENGTH);
        appendDecTableData(outputStream, tofSensor->thresholdMinDistanceMM, TOF_SENSOR_VALUE_THRESHOLD_MIN_COLUMN_LENGTH);
        appendDecTableData(outputStream, tofSensor->thresholdMaxDistanceMM, TOF_SENSOR_VALUE_THRESHOLD_MAX_COLUMN_LENGTH);
        appendDecTableData(outputStream, tofSensor->detectionThreshold, TOF_SENSOR_VALUE_DETECTION_THRESHOLD_COUNT_COLUMN_LENGTH);
        appendDecfTableData(outputStream, radToDeg(tofSensor->beamAngleRadian), TOF_SENSOR_VALUE_BEAM_ANGLE_DEGREE_LENGTH);
        appendDecfTableData(outputStream, radToDeg(tofSensor->orientationRadian), TOF_SENSOR_VALUE_ORIENTATION_ANGLE_DEGREE_LENGTH);
        appendDecfTableData(outputStream, tofSensor->distanceFromRobotCenter, TOF_SENSOR_VALUE_DISTANCE_FROM_ROBOT_CENTER_MM_COLUMN_LENGTH);
        appendDecfTableData(outputStream, radToDeg(tofSensor->angleFromRobotCenterRadian), TOF_SENSOR_VALUE_ANGLE_FROM_ROBOT_CENTER_DEGREE_COLUMN_LENGTH);

        appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);
    }

    appendTableHeaderSeparatorLine(outputStream);
}

// ------------------------------------------------------ NETWORK --------------------------------------------------

/**
* Private.
*/
void printTofSensorNetworkDebugTableHeader(OutputStream* outputStream) {
    println(outputStream);
    appendTableHeaderSeparatorLine(outputStream);
    // First header line
    appendStringHeader(outputStream, "Id", TOF_SENSOR_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Name", TOF_SENSOR_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Enab.", TOF_SENSOR_ENABLE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "I2c", TOF_SENSOR_I2C_BUS_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Chg.", TOF_SENSOR_CHANGE_ADRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "I2c", TOF_SENSOR_TARGET_ADRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Use", TOF_SENSOR_USE_MULTIPLEXER_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Multip.", TOF_SENSOR_MULTIPLEXER_CHANNEL_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Restart", TOF_SENSOR_RESTART_IO_EXPANDER_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Restart", TOF_SENSOR_RESTART_IO_EXPANDER_IO_INDEX_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);

    // Second header line
    appendStringHeader(outputStream, "", TOF_SENSOR_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_ENABLE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Bus", TOF_SENSOR_I2C_BUS_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Addr", TOF_SENSOR_CHANGE_ADRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Addr", TOF_SENSOR_TARGET_ADRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Multip.", TOF_SENSOR_USE_MULTIPLEXER_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Channel", TOF_SENSOR_MULTIPLEXER_CHANNEL_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Index", TOF_SENSOR_RESTART_IO_EXPANDER_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "IO Index", TOF_SENSOR_RESTART_IO_EXPANDER_IO_INDEX_COLUMN_LENGTH);
    
    appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);

    appendTableHeaderSeparatorLine(outputStream);
}


void printTofSensorNetworkTable(OutputStream* outputStream, TofSensorList* tofSensorList) {
    printTofSensorNetworkDebugTableHeader(outputStream);
    unsigned int index;
    for (index = 0; index < tofSensorList->size; index++) {
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, index);

        appendDecTableData(outputStream, index, TOF_SENSOR_INDEX_COLUMN_LENGTH);
        appendStringTableData(outputStream, tofSensor->name, TOF_SENSOR_NAME_COLUMN_LENGTH);
        appendBoolAsStringTableData(outputStream, tofSensor->enabled, TOF_SENSOR_ENABLE_COLUMN_LENGTH);
        // Network
        appendDecTableData(outputStream, tofSensor->i2cBusIndex, TOF_SENSOR_I2C_BUS_INDEX_COLUMN_LENGTH);
        appendBoolAsStringTableData(outputStream, tofSensor->changeAddress, TOF_SENSOR_CHANGE_ADRESS_COLUMN_LENGTH);
        appendHex2TableData(outputStream, tofSensor->targetAddress, TOF_SENSOR_TARGET_ADRESS_COLUMN_LENGTH);
        appendBoolAsStringTableData(outputStream, tofSensor->multiplexer != NULL, TOF_SENSOR_USE_MULTIPLEXER_COLUMN_LENGTH);
        appendDecTableData(outputStream, tofSensor->multiplexerChannel, TOF_SENSOR_MULTIPLEXER_CHANNEL_COLUMN_LENGTH);
        // Restart
        appendDecTableData(outputStream, tofSensor->hardwareRestartIOExpanderIndex, TOF_SENSOR_RESTART_IO_EXPANDER_INDEX_COLUMN_LENGTH);
        appendDecTableData(outputStream, tofSensor->hardwareRestartIOExpanderIoIndex, TOF_SENSOR_RESTART_IO_EXPANDER_IO_INDEX_COLUMN_LENGTH);

        appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);
    }

    appendTableHeaderSeparatorLine(outputStream);
}

// -------------------------------------------------- DETECTION ----------------------------------------------------

/**
* Private.
*/
void printTofSensorDetectionDebugTableHeader(OutputStream* outputStream) {
    println(outputStream);
    appendTableHeaderSeparatorLine(outputStream);
    // First header line
    appendStringHeader(outputStream, "Id", TOF_SENSOR_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Name", TOF_SENSOR_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Enab.", TOF_SENSOR_ENABLE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Thres", TOF_SENSOR_VALUE_THRESHOLD_MAX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Thres", TOF_SENSOR_VALUE_THRESHOLD_MIN_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Detect.", TOF_SENSOR_VALUE_DETECTION_THRESHOLD_COUNT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Detect.", TOF_SENSOR_VALUE_DETECTED_COUNT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Dist.", TOF_SENSOR_VALUE_DISTANCE_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "In", TOF_SENSOR_VALUE_DISTANCE_IN_RANGE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Dist.", TOF_SENSOR_VALUE_DISTANCE_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Detect. X", TOF_SENSOR_VALUE_OBJECT_X_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Detect. Y", TOF_SENSOR_VALUE_OBJECT_Y_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);
    
    // Second header line
    appendStringHeader(outputStream, "", TOF_SENSOR_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_ENABLE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Hold", TOF_SENSOR_VALUE_THRESHOLD_MAX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Hold", TOF_SENSOR_VALUE_THRESHOLD_MIN_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Thres", TOF_SENSOR_VALUE_DETECTION_THRESHOLD_COUNT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Count", TOF_SENSOR_VALUE_DETECTED_COUNT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", TOF_SENSOR_VALUE_DISTANCE_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Range.", TOF_SENSOR_VALUE_DISTANCE_IN_RANGE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", TOF_SENSOR_VALUE_DISTANCE_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", TOF_SENSOR_VALUE_OBJECT_X_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", TOF_SENSOR_VALUE_OBJECT_Y_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);

    // Third header line
    appendStringHeader(outputStream, "", TOF_SENSOR_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_ENABLE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", TOF_SENSOR_VALUE_THRESHOLD_MAX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", TOF_SENSOR_VALUE_THRESHOLD_MIN_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Hold", TOF_SENSOR_VALUE_DETECTION_THRESHOLD_COUNT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_VALUE_DETECTED_COUNT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(Dec)", TOF_SENSOR_VALUE_DISTANCE_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_VALUE_DISTANCE_IN_RANGE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(Hex)", TOF_SENSOR_VALUE_DISTANCE_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(Dec)", TOF_SENSOR_VALUE_OBJECT_X_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(Dec)", TOF_SENSOR_VALUE_OBJECT_Y_COLUMN_LENGTH);

    appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);

    appendTableHeaderSeparatorLine(outputStream);
}

void printTofSensorDetectionTable(OutputStream* outputStream, TofSensorList* tofSensorList, Point* pointOfView, float pointOfViewAngleRadian) {
    printTofSensorDetectionDebugTableHeader(outputStream);
    unsigned int index;
    for (index = 0; index < tofSensorList->size; index++) {
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, index);
        
        appendDecTableData(outputStream, index, TOF_SENSOR_INDEX_COLUMN_LENGTH);
        appendStringTableData(outputStream, tofSensor->name, TOF_SENSOR_NAME_COLUMN_LENGTH);
        appendBoolAsStringTableData(outputStream, tofSensor->enabled, TOF_SENSOR_ENABLE_COLUMN_LENGTH);

        // DISTANCE & DETECTION COUNT THRESHOLD
        appendDecTableData(outputStream, tofSensor->thresholdMinDistanceMM, TOF_SENSOR_VALUE_THRESHOLD_MIN_COLUMN_LENGTH);
        appendDecTableData(outputStream, tofSensor->thresholdMaxDistanceMM, TOF_SENSOR_VALUE_THRESHOLD_MAX_COLUMN_LENGTH);
        appendDecTableData(outputStream, tofSensor->detectionThreshold, TOF_SENSOR_VALUE_DETECTION_THRESHOLD_COUNT_COLUMN_LENGTH);
        appendDecTableData(outputStream, tofSensor->detectedCount, TOF_SENSOR_VALUE_DETECTED_COUNT_COLUMN_LENGTH);

        // DISTANCE
        unsigned int distance = tofSensor->tofGetDistanceMM(tofSensor);
        appendDecTableData(outputStream, distance, TOF_SENSOR_VALUE_DISTANCE_DEC_COLUMN_LENGTH);
        bool inRange = isTofDistanceInRange(tofSensor);
        appendBoolAsStringTableData(outputStream, inRange, TOF_SENSOR_VALUE_DISTANCE_IN_RANGE_COLUMN_LENGTH);

        appendHex4TableData(outputStream, distance, TOF_SENSOR_VALUE_DISTANCE_HEX_COLUMN_LENGTH);

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