#include "tofListDebug.h"

#include <stdlib.h>

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#include "../../common/math/cenMath.h"

#include "tof.h"
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
    appendStringHeader(outputStream, "Type", TOF_SENSOR_USAGE_TYPE_COLUMN_LENGTH);
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
    appendStringHeader(outputStream, "", TOF_SENSOR_USAGE_TYPE_COLUMN_LENGTH);
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
    appendStringHeader(outputStream, "", TOF_SENSOR_USAGE_TYPE_COLUMN_LENGTH);
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
    appendStringHeader(outputStream, "", TOF_SENSOR_USAGE_TYPE_COLUMN_LENGTH);
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
        addTofSensorUsageTypeShortTableData(outputStream, tofSensor->usageType, TOF_SENSOR_USAGE_TYPE_COLUMN_LENGTH);
        appendBoolAsStringTableData(outputStream, tofSensor->enabled, TOF_SENSOR_ENABLE_COLUMN_LENGTH);
        appendDecTableData(outputStream, tofSensor->thresholdDistanceMM, TOF_SENSOR_VALUE_THRESHOLD_MIN_COLUMN_LENGTH);
        appendDecTableData(outputStream, tofSensor->thresholdDistanceMM, TOF_SENSOR_VALUE_THRESHOLD_MAX_COLUMN_LENGTH);
        appendDecTableData(outputStream, tofSensor->detectionThreshold, TOF_SENSOR_VALUE_DETECTION_THRESHOLD_COUNT_COLUMN_LENGTH);
        appendDecfTableData(outputStream, radToDeg(tofSensor->beamAngleRadian), TOF_SENSOR_VALUE_BEAM_ANGLE_DEGREE_LENGTH);
        appendDecfTableData(outputStream, radToDeg(tofSensor->orientationRadian), TOF_SENSOR_VALUE_ORIENTATION_ANGLE_DEGREE_LENGTH);
        appendDecfTableData(outputStream, tofSensor->distanceFromRobotCenter, TOF_SENSOR_VALUE_DISTANCE_FROM_ROBOT_CENTER_MM_COLUMN_LENGTH);
        appendDecfTableData(outputStream, radToDeg(tofSensor->angleFromRobotCenterRadian), TOF_SENSOR_VALUE_ANGLE_FROM_ROBOT_CENTER_DEGREE_COLUMN_LENGTH);

        appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);
    }

    appendTableHeaderSeparatorLine(outputStream);
}

// NETWORK PART

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
    appendStringHeader(outputStream, "Chg.", TOF_SENSOR_CHANGE_ADRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Use", TOF_SENSOR_USE_MULTIPLEXER_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Multip.", TOF_SENSOR_MULTIPLEXER_CHANNEL_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);

    // Second header line
    appendStringHeader(outputStream, "", TOF_SENSOR_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_ENABLE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Addr", TOF_SENSOR_CHANGE_ADRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Multip.", TOF_SENSOR_USE_MULTIPLEXER_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Channel", TOF_SENSOR_MULTIPLEXER_CHANNEL_COLUMN_LENGTH);
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
        appendBoolAsStringTableData(outputStream, tofSensor->changeAddress, TOF_SENSOR_CHANGE_ADRESS_COLUMN_LENGTH);
        appendBoolAsStringTableData(outputStream, tofSensor->useMultiplexer, TOF_SENSOR_USE_MULTIPLEXER_COLUMN_LENGTH);
        appendDecTableData(outputStream, tofSensor->multiplexerChannel, TOF_SENSOR_MULTIPLEXER_CHANNEL_COLUMN_LENGTH);

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
    appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);

    appendTableHeaderSeparatorLine(outputStream);
}

void printTofSensorDetectionTable(OutputStream* outputStream, TofSensorList* tofSensorList, Point* pointOfView, float pointOfViewAngleRadian) {
    printTofSensorNetworkDebugTableHeader(outputStream);
    unsigned int index;
    for (index = 0; index < tofSensorList->size; index++) {
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, index);

        appendDecTableData(outputStream, index, TOF_SENSOR_INDEX_COLUMN_LENGTH);
        appendStringTableData(outputStream, tofSensor->name, TOF_SENSOR_NAME_COLUMN_LENGTH);
        appendBoolAsStringTableData(outputStream, tofSensor->enabled, TOF_SENSOR_ENABLE_COLUMN_LENGTH);

        // TODO 

        appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);
    }

    appendTableHeaderSeparatorLine(outputStream);
}