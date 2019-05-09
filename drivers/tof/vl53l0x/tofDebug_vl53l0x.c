#include "tofDebug_vl53l0x.h"

#include <stdlib.h>

#include "../../../common/2d/2d.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"

#include "../../../common/math/cenMath.h"

#include "../../../robot/gameboard/gameboard.h"

#include "../tof.h"
#include "../tofList.h"
#include "tof_vl53l0x.h"

#define TOF_SENSOR_VL53L0X_INDEX_COLUMN_LENGTH		                        6
#define TOF_SENSOR_VL53L0X_NAME_COLUMN_LENGTH                               13
#define TOF_SENSOR_VL53L0X_ENABLE_COLUMN_LENGTH                             7
#define TOF_SENSOR_VL53L0X_CHANGE_ADRESS_COLUMN_LENGTH                      7

#define TOF_SENSOR_VL53L0X_I2C_ADDRESS_COLUMN_LENGTH                        6
#define TOF_SENSOR_VL53L0X_STATUS_COLUMN_LENGTH                             7
#define TOF_SENSOR_VL53L0X_VALUE_THRESHOLD_COLUMN_LENGTH                    5
#define TOF_SENSOR_VL53L0X_VALUE_ORIENTATION_COLUMN_LENGTH                  7
#define TOF_SENSOR_VL53L0X_VALUE_DEC_COLUMN_LENGTH                          7
#define TOF_SENSOR_VL53L0X_VALUE_HEX_COLUMN_LENGTH                          7
#define TOF_SENSOR_VL53L0X_VALUE_OBJECT_X_COLUMN_LENGTH                     7
#define TOF_SENSOR_VL53L0X_VALUE_OBJECT_Y_COLUMN_LENGTH                     7
#define TOF_SENSOR_VL53L0X_VALUE_OBJECT_IN_GAME_BOARD_COLUMN_LENGTH         5

#define TOF_SENSOR_VL53L0X_LAST_COLUMN		                                0

/**
* Private.
*/
void printTofSensorDebugTableHeaderVL53L0X(OutputStream* outputStream) {
    println(outputStream);
    appendTableHeaderSeparatorLine(outputStream);
    // First line
    appendStringHeader(outputStream, "Idx", TOF_SENSOR_VL53L0X_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Name", TOF_SENSOR_VL53L0X_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Enable", TOF_SENSOR_VL53L0X_ENABLE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Change", TOF_SENSOR_VL53L0X_CHANGE_ADRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Dev", TOF_SENSOR_VL53L0X_I2C_ADDRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Status", TOF_SENSOR_VL53L0X_STATUS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Thres", TOF_SENSOR_VL53L0X_VALUE_THRESHOLD_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Orient.", TOF_SENSOR_VL53L0X_VALUE_ORIENTATION_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Dist", TOF_SENSOR_VL53L0X_VALUE_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Dist", TOF_SENSOR_VL53L0X_VALUE_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Detect.", TOF_SENSOR_VL53L0X_VALUE_OBJECT_X_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Detect.", TOF_SENSOR_VL53L0X_VALUE_OBJECT_Y_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Detect.", TOF_SENSOR_VL53L0X_VALUE_OBJECT_IN_GAME_BOARD_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, TOF_SENSOR_VL53L0X_LAST_COLUMN);

    // Second header line
    appendStringHeader(outputStream, "(Dec)", TOF_SENSOR_VL53L0X_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_VL53L0X_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_VL53L0X_ENABLE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Address", TOF_SENSOR_VL53L0X_CHANGE_ADRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "I2C", TOF_SENSOR_VL53L0X_I2C_ADDRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_VL53L0X_STATUS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "hold", TOF_SENSOR_VL53L0X_VALUE_THRESHOLD_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(Deg)", TOF_SENSOR_VL53L0X_VALUE_ORIENTATION_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(Dec)", TOF_SENSOR_VL53L0X_VALUE_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(Hex)", TOF_SENSOR_VL53L0X_VALUE_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "x", TOF_SENSOR_VL53L0X_VALUE_OBJECT_X_COLUMN_LENGTH);
    appendStringHeader(outputStream, "y", TOF_SENSOR_VL53L0X_VALUE_OBJECT_Y_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, TOF_SENSOR_VL53L0X_LAST_COLUMN);
    
    // Third header line
    appendStringHeader(outputStream, "", TOF_SENSOR_VL53L0X_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_VL53L0X_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_VL53L0X_ENABLE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_VL53L0X_CHANGE_ADRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Addr", TOF_SENSOR_VL53L0X_I2C_ADDRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_VL53L0X_STATUS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", TOF_SENSOR_VL53L0X_VALUE_THRESHOLD_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TOF_SENSOR_VL53L0X_VALUE_ORIENTATION_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", TOF_SENSOR_VL53L0X_VALUE_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", TOF_SENSOR_VL53L0X_VALUE_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", TOF_SENSOR_VL53L0X_VALUE_OBJECT_X_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", TOF_SENSOR_VL53L0X_VALUE_OBJECT_Y_COLUMN_LENGTH);
    
    appendEndOfTableColumn(outputStream, TOF_SENSOR_VL53L0X_LAST_COLUMN);
    appendTableHeaderSeparatorLine(outputStream);
}

void printTofSensorTableVL53L0X(OutputStream* outputStream, TofSensorList* tofSensorList, Point* pointOfView, float pointOfViewAngleRadian) {
    appendStringAndDecLN(outputStream, "TofSensorList:size=", tofSensorList->size);
    
    printTofSensorDebugTableHeaderVL53L0X(outputStream);
    unsigned int index;
    for (index = 0; index < tofSensorList->size; index++) {
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, index);
        
        if (!tofSensor->enabled) {
            continue;
        }

        // Tof Configuration Properties
        appendDecTableData(outputStream, index, TOF_SENSOR_VL53L0X_INDEX_COLUMN_LENGTH);      

        appendStringTableData(outputStream, tofSensor->name, TOF_SENSOR_VL53L0X_NAME_COLUMN_LENGTH);
        appendBoolAsStringTableData(outputStream, tofSensor->enabled, TOF_SENSOR_VL53L0X_ENABLE_COLUMN_LENGTH);
        appendBoolAsStringTableData(outputStream, tofSensor->changeAddress, TOF_SENSOR_VL53L0X_CHANGE_ADRESS_COLUMN_LENGTH);

        
        TofSensorVL53L0X* tofSensorVL53L0X = getTofSensorVL53L0X(tofSensor);
        if (tofSensorVL53L0X == NULL || !tofSensor->enabled) {
            appendStringTableData(outputStream, "NULL", TOF_SENSOR_VL53L0X_I2C_ADDRESS_COLUMN_LENGTH);
            appendStringTableData(outputStream, "N/A", TOF_SENSOR_VL53L0X_STATUS_COLUMN_LENGTH);

            appendDecfTableData(outputStream, tofSensor->thresholdDistanceMM, TOF_SENSOR_VL53L0X_VALUE_THRESHOLD_COLUMN_LENGTH);
            appendDecfTableData(outputStream, radToDeg(tofSensor->orientationRadian), TOF_SENSOR_VL53L0X_VALUE_ORIENTATION_COLUMN_LENGTH);
            
            appendStringTableData(outputStream, "N/A", TOF_SENSOR_VL53L0X_VALUE_DEC_COLUMN_LENGTH);
            appendStringTableData(outputStream, "N/A", TOF_SENSOR_VL53L0X_VALUE_HEX_COLUMN_LENGTH);

            appendStringTableData(outputStream, "N/A", TOF_SENSOR_VL53L0X_VALUE_OBJECT_X_COLUMN_LENGTH);        
            appendStringTableData(outputStream, "N/A", TOF_SENSOR_VL53L0X_VALUE_OBJECT_Y_COLUMN_LENGTH);        

        }
        else {
            // VL53L0X_Dev_t* tofDevice = &(tofSensorVL53L0X->device);
            // uint8_t i2cAddress = tofDevice->I2cDevAddr;

            I2cBusConnection* i2cBusConnection = tofSensorVL53L0X->i2cBusConnection;        
            if (i2cBusConnection != NULL) {
                unsigned char i2cBusConnectionAddress = i2cBusConnection->i2cAddress;
                appendHex2TableData(outputStream, i2cBusConnectionAddress, TOF_SENSOR_VL53L0X_I2C_ADDRESS_COLUMN_LENGTH);
            }
            else {
                appendStringTableData(outputStream, "Bus NULL", TOF_SENSOR_VL53L0X_I2C_ADDRESS_COLUMN_LENGTH);
            }

            uint8_t status = tofSensorVL53L0X->status;
            appendHex2TableData(outputStream, status, TOF_SENSOR_VL53L0X_STATUS_COLUMN_LENGTH);
        
            appendDecfTableData(outputStream, tofSensor->thresholdDistanceMM, TOF_SENSOR_VL53L0X_VALUE_THRESHOLD_COLUMN_LENGTH);
            appendDecfTableData(outputStream, radToDeg(tofSensor->orientationRadian), TOF_SENSOR_VL53L0X_VALUE_ORIENTATION_COLUMN_LENGTH);
        
            unsigned int distance = tofSensor->tofGetDistanceMM(tofSensor);
            appendDecTableData(outputStream, distance, TOF_SENSOR_VL53L0X_VALUE_DEC_COLUMN_LENGTH);
            appendHex4TableData(outputStream, distance, TOF_SENSOR_VL53L0X_VALUE_HEX_COLUMN_LENGTH);

            // DetectedPoint if any
            Point detectedPoint;
            bool detected = tofComputeDetectedPointIfAny(tofSensor, pointOfView, pointOfViewAngleRadian, &detectedPoint);
            // Distance to the point of View only if in the Threshold
            if (detected) {
                appendDecfTableData(outputStream, detectedPoint.x, TOF_SENSOR_VL53L0X_VALUE_OBJECT_X_COLUMN_LENGTH);
                appendDecfTableData(outputStream, detectedPoint.y, TOF_SENSOR_VL53L0X_VALUE_OBJECT_Y_COLUMN_LENGTH);
                bool isColliding = isPointInTheCollisionArea(NULL, &detectedPoint);
                appendBoolAsStringTableData(outputStream, isColliding, TOF_SENSOR_VL53L0X_VALUE_OBJECT_IN_GAME_BOARD_COLUMN_LENGTH);
            }
            else {
                appendStringTableData(outputStream, "-", TOF_SENSOR_VL53L0X_VALUE_OBJECT_X_COLUMN_LENGTH);
                appendStringTableData(outputStream, "-", TOF_SENSOR_VL53L0X_VALUE_OBJECT_Y_COLUMN_LENGTH);        
                appendStringTableData(outputStream, "-", TOF_SENSOR_VL53L0X_VALUE_OBJECT_IN_GAME_BOARD_COLUMN_LENGTH);        
            }
        }
        appendEndOfTableColumn(outputStream, TOF_SENSOR_VL53L0X_LAST_COLUMN);
    }

    appendTableHeaderSeparatorLine(outputStream);
}
