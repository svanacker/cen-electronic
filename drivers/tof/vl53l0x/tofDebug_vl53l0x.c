#include "tofDebug_vl53l0x.h"

#include <stdlib.h>

#include "../../../common/2d/2d.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"

#include "../../../common/math/cenMath.h"

#include "../../../robot/gameboard/gameboard.h"

#include "../../../drivers/tof/tof.h"
#include "../../../drivers/tof/tofDetectionUtils.h"
#include "../../../drivers/tof/tofDebug.h"
#include "../../../drivers/tof/tofList.h"
#include "../../../drivers/tof/tofListDebug.h"

#include "tof_vl53l0x.h"

// CONFIG

// NETWORK
#define TOF_SENSOR_VL53L0X_I2C_ADDRESS_COLUMN_LENGTH                       10
#define TOF_SENSOR_VL53L0X_STATUS_COLUMN_LENGTH                             7

// DETECTION

// ------------------------------------ CONFIG --------------------------------

void printTofSensorConfigTableVL53L0X(OutputStream* outputStream, TofSensorList* tofSensorList) {
    // We rely on the classical implementation
    printTofSensorConfigTable(outputStream, tofSensorList);
}

// ------------------------------------ NETWORK -------------------------------

/**
* Private.
*/
void printTofSensorNetworkDebugTableHeaderVL53L0X(OutputStream* outputStream) {
    appendTableHeaderSeparatorLine(outputStream);
    // First header line
    appendStringHeader(outputStream, "Id", TOF_SENSOR_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Name", TOF_SENSOR_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Enab.", TOF_SENSOR_ENABLE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "I2c", TOF_SENSOR_I2C_BUS_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Chg.", TOF_SENSOR_CHANGE_ADRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "I2c", TOF_SENSOR_TARGET_ADRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Use", TOF_SENSOR_USE_MULTIPLEXER_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Multi", TOF_SENSOR_MULTIPLEXER_CHANNEL_COLUMN_LENGTH);
    appendStringHeader(outputStream, "I2c Addr.", TOF_SENSOR_VL53L0X_I2C_ADDRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "VL53L0X", TOF_SENSOR_VL53L0X_STATUS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Hard", TOF_SENSOR_HAS_HARDWARE_RESTART_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Restart", TOF_SENSOR_HARDWARE_RESTART_IO_EXPANDER_IO_INDEX_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);

    // Second header line
    appendStringHeader(outputStream, "", TOF_SENSOR_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_ENABLE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Bus Addr", TOF_SENSOR_I2C_BUS_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Addr", TOF_SENSOR_CHANGE_ADRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Targ.", TOF_SENSOR_TARGET_ADRESS_COLUMN_LENGTH);

    appendStringHeader(outputStream, "Multip.", TOF_SENSOR_USE_MULTIPLEXER_COLUMN_LENGTH);
    appendStringHeader(outputStream, "plexer", TOF_SENSOR_MULTIPLEXER_CHANNEL_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(Hex)", TOF_SENSOR_VL53L0X_I2C_ADDRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Status", TOF_SENSOR_VL53L0X_STATUS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Reset ?", TOF_SENSOR_HAS_HARDWARE_RESTART_COLUMN_LENGTH);
    appendStringHeader(outputStream, "IO Index", TOF_SENSOR_HARDWARE_RESTART_IO_EXPANDER_IO_INDEX_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);
    
    // Third header line
    appendStringHeader(outputStream, "", TOF_SENSOR_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_ENABLE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_I2C_BUS_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_CHANGE_ADRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Addr", TOF_SENSOR_TARGET_ADRESS_COLUMN_LENGTH);

    appendStringHeader(outputStream, ".", TOF_SENSOR_USE_MULTIPLEXER_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Channel", TOF_SENSOR_MULTIPLEXER_CHANNEL_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_VL53L0X_I2C_ADDRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_VL53L0X_STATUS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_HAS_HARDWARE_RESTART_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_HARDWARE_RESTART_IO_EXPANDER_IO_INDEX_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);

    appendTableHeaderSeparatorLine(outputStream);
}

void printTofSensorNetworkTableVL53L0X(OutputStream* outputStream, TofSensorList* tofSensorList) {
    printTofSensorNetworkDebugTableHeaderVL53L0X(outputStream);
    unsigned int index;
    for (index = 0; index < tofSensorList->size; index++) {
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, index);

        appendDecTableData(outputStream, index, TOF_SENSOR_INDEX_COLUMN_LENGTH);
        appendStringTableData(outputStream, tofSensor->name, TOF_SENSOR_NAME_COLUMN_LENGTH);
        appendBoolAsStringTableData(outputStream, tofSensor->enabled, TOF_SENSOR_ENABLE_COLUMN_LENGTH);
        appendDecTableData(outputStream, tofSensor->i2cBusIndex, TOF_SENSOR_I2C_BUS_INDEX_COLUMN_LENGTH);
        appendBoolAsStringTableData(outputStream, tofSensor->changeAddress, TOF_SENSOR_CHANGE_ADRESS_COLUMN_LENGTH);
        appendHex2TableData(outputStream, tofSensor->targetAddress, TOF_SENSOR_TARGET_ADRESS_COLUMN_LENGTH);
        appendBoolAsStringTableData(outputStream, tofSensor->multiplexer != NULL, TOF_SENSOR_USE_MULTIPLEXER_COLUMN_LENGTH);
        appendDecTableData(outputStream, tofSensor->multiplexerChannel, TOF_SENSOR_MULTIPLEXER_CHANNEL_COLUMN_LENGTH);
        
        TofSensorVL53L0X* tofSensorVL53L0X = getTofSensorVL53L0X(tofSensor);
        // I2C ADDRESSS
        if (tofSensorVL53L0X == NULL) {
            appendStringTableData(outputStream, "N/A", TOF_SENSOR_VL53L0X_I2C_ADDRESS_COLUMN_LENGTH);
        }
        else {
            I2cBusConnection* i2cBusConnection = tofSensorVL53L0X->i2cBusConnection;        
            if (i2cBusConnection != NULL) {
                unsigned char i2cBusConnectionAddress = i2cBusConnection->i2cAddress;
                appendHex2TableData(outputStream, i2cBusConnectionAddress, TOF_SENSOR_VL53L0X_I2C_ADDRESS_COLUMN_LENGTH);
            }
            else {
                appendStringTableData(outputStream, "Bus NULL", TOF_SENSOR_VL53L0X_I2C_ADDRESS_COLUMN_LENGTH);
            }
        }
        if (!tofSensor->enabled) {
            appendStringTableData(outputStream, "N/A", TOF_SENSOR_VL53L0X_STATUS_COLUMN_LENGTH);
        }
        else {
            // STATUS
            uint8_t status = tofSensorVL53L0X->status;
            appendHex2TableData(outputStream, status, TOF_SENSOR_VL53L0X_STATUS_COLUMN_LENGTH);
        }
        // Restart
        appendBoolAsStringTableData(outputStream, tofSensor->hardwareRestartIOExpander != NULL, TOF_SENSOR_HAS_HARDWARE_RESTART_COLUMN_LENGTH);
        appendDecTableData(outputStream, tofSensor->hardwareRestartIOExpanderIoIndex, TOF_SENSOR_HARDWARE_RESTART_IO_EXPANDER_IO_INDEX_COLUMN_LENGTH);

        appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);
    }

    appendTableHeaderSeparatorLine(outputStream);
}

// ------------------------------------- DETECTION ----------------------------

/**
* Private.
*/
void printTofSensorDetectionDebugTableHeaderVL53L0X(OutputStream* outputStream) {
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
    appendStringHeader(outputStream, "Dist.", TOF_SENSOR_VALUE_DISTANCE_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Detect.", TOF_SENSOR_VALUE_OBJECT_X_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Detect.", TOF_SENSOR_VALUE_OBJECT_Y_COLUMN_LENGTH);
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
    appendStringHeader(outputStream, "(mm)", TOF_SENSOR_VALUE_DISTANCE_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "X", TOF_SENSOR_VALUE_OBJECT_X_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Y", TOF_SENSOR_VALUE_OBJECT_Y_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);

    // Third header line
    appendStringHeader(outputStream, "", TOF_SENSOR_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_ENABLE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(max)", TOF_SENSOR_VALUE_THRESHOLD_MAX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(min)", TOF_SENSOR_VALUE_THRESHOLD_MIN_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Hold", TOF_SENSOR_VALUE_DETECTION_THRESHOLD_COUNT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(Dec)", TOF_SENSOR_VALUE_DETECTED_COUNT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(Dec)", TOF_SENSOR_VALUE_DISTANCE_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(Hex)", TOF_SENSOR_VALUE_DISTANCE_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", TOF_SENSOR_VALUE_OBJECT_X_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", TOF_SENSOR_VALUE_OBJECT_Y_COLUMN_LENGTH);

    // 4th header line
    appendStringHeader(outputStream, "", TOF_SENSOR_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_ENABLE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", TOF_SENSOR_VALUE_THRESHOLD_MAX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", TOF_SENSOR_VALUE_THRESHOLD_MIN_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Hold", TOF_SENSOR_VALUE_DETECTION_THRESHOLD_COUNT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_VALUE_DETECTED_COUNT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_VALUE_DISTANCE_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_VALUE_DISTANCE_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(Dec)", TOF_SENSOR_VALUE_OBJECT_X_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(Dec)", TOF_SENSOR_VALUE_OBJECT_Y_COLUMN_LENGTH);
    
    appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);

    appendTableHeaderSeparatorLine(outputStream);
}

void printTofSensorDetectionTableVL53L0X(OutputStream* outputStream, TofSensorList* tofSensorList, Point* pointOfView, float pointOfViewAngleRadian) {
    printTofSensorDetectionDebugTableHeaderVL53L0X(outputStream);
    unsigned int index;
    for (index = 0; index < tofSensorList->size; index++) {
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, index);
        
        appendDecTableData(outputStream, index, TOF_SENSOR_INDEX_COLUMN_LENGTH);
        appendStringTableData(outputStream, tofSensor->name, TOF_SENSOR_NAME_COLUMN_LENGTH);
        appendBoolAsStringTableData(outputStream, tofSensor->enabled, TOF_SENSOR_ENABLE_COLUMN_LENGTH);

        // DISTANCE & DETECTION COUNT THRESHOLD
        appendDecfTableData(outputStream, tofSensor->thresholdMinDistanceMM, TOF_SENSOR_VALUE_THRESHOLD_MIN_COLUMN_LENGTH);
        appendDecfTableData(outputStream, tofSensor->thresholdMaxDistanceMM, TOF_SENSOR_VALUE_THRESHOLD_MAX_COLUMN_LENGTH);
        appendDecTableData(outputStream, tofSensor->detectionThreshold, TOF_SENSOR_VALUE_DETECTION_THRESHOLD_COUNT_COLUMN_LENGTH);
        appendDecTableData(outputStream, tofSensor->detectedCount, TOF_SENSOR_VALUE_DETECTED_COUNT_COLUMN_LENGTH);

        // DISTANCE
        TofSensorVL53L0X* tofSensorVL53L0X = getTofSensorVL53L0X(tofSensor);
        if (tofSensorVL53L0X == NULL || !tofSensor->enabled) {
            appendStringTableData(outputStream, "N/A", TOF_SENSOR_VALUE_DISTANCE_DEC_COLUMN_LENGTH);
            appendStringTableData(outputStream, "N/A", TOF_SENSOR_VALUE_DISTANCE_HEX_COLUMN_LENGTH);

            appendStringTableData(outputStream, "N/A", TOF_SENSOR_VALUE_OBJECT_X_COLUMN_LENGTH);        
            appendStringTableData(outputStream, "N/A", TOF_SENSOR_VALUE_OBJECT_Y_COLUMN_LENGTH);        

        }
        else {
            unsigned int distance = tofSensor->tofGetDistanceMM(tofSensor);
            appendDecTableData(outputStream, distance, TOF_SENSOR_VALUE_DISTANCE_DEC_COLUMN_LENGTH);
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
        }
        appendEndOfTableColumn(outputStream, TOF_SENSOR_LAST_COLUMN);
    }

    appendTableHeaderSeparatorLine(outputStream);
}
