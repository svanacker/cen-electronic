#include "tofDebug_vl53l0x.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"

#include "../tof.h"
#include "../tofList.h"
#include "tof_vl53l0x.h"

#define TOF_SENSOR_VL53L0X_INDEX_COLUMN_LENGTH		      10
#define TOF_SENSOR_VL53L0X_I2C_ADDRESS_COLUMN_LENGTH      15
#define TOF_SENSOR_VL53L0X_STATUS_COLUMN_LENGTH           15
#define TOF_SENSOR_VL53L0X_VALUE_DEC_COLUMN_LENGTH        15
#define TOF_SENSOR_VL53L0X_VALUE_HEX_COLUMN_LENGTH        15
#define TOF_SENSOR_VL53L0X_LAST_COLUMN		              0

/**
* Private.
*/
void printTofSensorDebugTableHeaderVL53L0X(OutputStream* outputStream) {
    println(outputStream);
    appendTableHeaderSeparatorLine(outputStream);
    appendStringHeader(outputStream, "Index", TOF_SENSOR_VL53L0X_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Dev/I2C Addr", TOF_SENSOR_VL53L0X_I2C_ADDRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "I2C Bus Addr", TOF_SENSOR_VL53L0X_I2C_ADDRESS_COLUMN_LENGTH);
    
    
    appendStringHeader(outputStream, "Status", TOF_SENSOR_VL53L0X_STATUS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Dist (mm)", TOF_SENSOR_VL53L0X_VALUE_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Dist (mm) / Hex", TOF_SENSOR_VL53L0X_VALUE_HEX_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, TOF_SENSOR_VL53L0X_LAST_COLUMN);
    appendTableHeaderSeparatorLine(outputStream);
}

void printTofSensorTableVL53L0X(OutputStream* outputStream, TofSensorList* tofSensorList) {
    printTofSensorDebugTableHeaderVL53L0X(outputStream);
    unsigned int index;
    for (index = 0; index < tofSensorList->size; index++) {
        appendDecTableData(outputStream, index, TOF_SENSOR_VL53L0X_INDEX_COLUMN_LENGTH);

        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, index);
        unsigned int distance = tofSensor->tofGetDistanceMM(tofSensor);
        
        TofSensorVL53L0X* tofSensorVL53L0X = getTofSensorVL53L0X(tofSensor);
        VL53L0X_Dev_t* tofDevice = &(tofSensorVL53L0X->device);
        uint8_t i2cAddress = tofDevice->I2cDevAddr;
        
        I2cBusConnection* i2cBusConnection = tofSensorVL53L0X->i2cBusConnection;
        
        appendHex2TableData(outputStream, i2cAddress, TOF_SENSOR_VL53L0X_I2C_ADDRESS_COLUMN_LENGTH);
        unsigned char i2cBusConnectionAddress = i2cBusConnection->i2cAddress;

        appendHex2TableData(outputStream, i2cBusConnectionAddress, TOF_SENSOR_VL53L0X_I2C_ADDRESS_COLUMN_LENGTH);
        
        uint8_t status = tofSensorVL53L0X->status;
        appendHex2TableData(outputStream, status, TOF_SENSOR_VL53L0X_STATUS_COLUMN_LENGTH);

        appendDecTableData(outputStream, distance, TOF_SENSOR_VL53L0X_VALUE_DEC_COLUMN_LENGTH);
        appendHex4TableData(outputStream, distance, TOF_SENSOR_VL53L0X_VALUE_HEX_COLUMN_LENGTH);
        appendEndOfTableColumn(outputStream, TOF_SENSOR_VL53L0X_LAST_COLUMN);
    }

    appendTableHeaderSeparatorLine(outputStream);
}
