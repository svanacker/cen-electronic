#include "INA219Debug.h"

#include <math.h>

#include "../../common/error/error.h"

#include "../../common/i2c/i2cBusConnectionList.h"
#include "../../common/i2c/master/i2cMaster.h"

#include "../../common/log/logger.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"
#include "sensor/accelerometer/accelerometer.h"

// DEBUG CONFIG / REGISTERS

/**
* Private.
*/
void ina219_printRegisterListHeader(OutputStream* outputStream) {
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "#Reg", INA219_DEBUG_REG_COLUMN_LENGTH);
	appendStringHeader(outputStream, "#Reg Hex", INA219_DEBUG_REG_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Reg Name", INA219_DEBUG_REG_NAME_COLUMN_LENGTH); 
	appendStringHeader(outputStream, "R/W", INA219_DEBUG_REG_RW_COLUMN_LENGTH);       
    appendStringHeader(outputStream, "Dec Value", INA219_DEBUG_REG_VALUE_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Hex Value", INA219_DEBUG_REG_VALUE_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Bin Value", INA219_DEBUG_REG_VALUE_BIN_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, 0);
	appendTableHeaderSeparatorLine(outputStream);
}

/**
 * Private
 * @param i2cBusConnection
 */
void ina219_debugMainRegister(OutputStream* outputStream, I2cBusConnection* i2cBusConnection, unsigned char reg, const char* regName, const char* rw) {
    /*
    int value = ina219_read16(i2cBusConnection, reg);
	appendDecTableData(outputStream, reg, INA219_DEBUG_REG_COLUMN_LENGTH);
	appendHex2TableData(outputStream, reg, INA219_DEBUG_REG_HEX_COLUMN_LENGTH);
	appendStringTableData(outputStream, regName, INA219_DEBUG_REG_NAME_COLUMN_LENGTH);
	appendStringTableData(outputStream, rw, INA219_DEBUG_REG_RW_COLUMN_LENGTH);
    appendDecTableData(outputStream, value, INA219_DEBUG_REG_VALUE_DEC_COLUMN_LENGTH);
    appendHex2TableData(outputStream, value, INA219_DEBUG_REG_VALUE_HEX_COLUMN_LENGTH);
	appendBinary8TableData(outputStream, value, 4, INA219_DEBUG_REG_VALUE_BIN_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, 0);
    */
}

void ina219_debugMainRegisterList(OutputStream* outputStream, Accelerometer* accelerometer) {
    I2cBusConnection* i2cBusConnection = (I2cBusConnection*) accelerometer->object;
    ina219_printRegisterListHeader(outputStream);
    ina219_debugMainRegister(outputStream, i2cBusConnection, INA219_CONFIGURATION_REGISTER, "REG_CONF", "R/W");
    ina219_debugMainRegister(outputStream, i2cBusConnection, INA219_SHUNT_VOLTAGE_REGISTER, "REG_SHUNT_VOLTAGE", "R");
    ina219_debugMainRegister(outputStream, i2cBusConnection, INA219_BUS_VOLTAGE_REGISTER, "REG_BUS_VOLTAGE", "R");
    ina219_debugMainRegister(outputStream, i2cBusConnection, INA219_POWER_REGISTER, "REG_POWER", "R");
    ina219_debugMainRegister(outputStream, i2cBusConnection, INA219_CURRENT_REGISTER, "REG_CURRENT", "R");
    ina219_debugMainRegister(outputStream, i2cBusConnection, INA219_CALIBRATION_REGISTER, "REG_CALIBRATION", "R/W");

    appendTableHeaderSeparatorLine(outputStream);
}

// DEBUG VALUES

/**
 * Private
 * @param i2cBusConnection
 */
void ina219_debugMainRegisterAcceleratorData(OutputStream* outputStream, unsigned char low, unsigned char high, int value, float mgValue, const char* regName) {
	appendStringTableData(outputStream, regName, INA219_DEBUG_REG_COLUMN_LENGTH);
    appendHex2TableData(outputStream, high, INA219_DEBUG_REG_HEX_COLUMN_LENGTH);
    appendHex2TableData(outputStream, low, INA219_DEBUG_REG_HEX_COLUMN_LENGTH);
	appendHex4TableData(outputStream, value, INA219_DEBUG_REG_HEX_COLUMN_LENGTH);
	appendDecTableData(outputStream, value, INA219_DEBUG_REG_VALUE_DEC_COLUMN_LENGTH);
    appendDecfTableData(outputStream, mgValue, INA219_DEBUG_REG_VALUE_MG_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, 0);
}

void ina219_debugValueRegisterList(OutputStream* outputStream, Accelerometer* accelerometer) {
    /*
    AccelerometerData* accelerometerData = accelerometer->accelerometerData;
    adxl345_printAccelerometerDataListHeader(outputStream);
    adxl345_debugMainRegisterAcceleratorData(outputStream, accelerometerData->xRawLowValue, accelerometerData->xRawHighValue, accelerometerData->xRawValue, accelerometerData->milligXValue, "X");
    adxl345_debugMainRegisterAcceleratorData(outputStream, accelerometerData->yRawLowValue, accelerometerData->yRawHighValue, accelerometerData->yRawValue, accelerometerData->milligYValue, "Y");
    adxl345_debugMainRegisterAcceleratorData(outputStream, accelerometerData->zRawLowValue, accelerometerData->zRawHighValue, accelerometerData->zRawValue, accelerometerData->milligZValue, "Z");

    appendTableHeaderSeparatorLine(outputStream);
    */
}

/*
void adxl345_debugValueRegisterListIfShock(OutputStream* outputStream, I2cBusConnection* i2cBusConnection, AccelerometerData* accelerometerData) {
    unsigned int sampleCount = adx345_readSampleCount(i2cBusConnection);
    if (sampleCount == 0) {
        return;
    }
    adxl345_readAccelerometerData(i2cBusConnection, accelerometerData);
    if (fabs(accelerometerData->milligXValue) > 2300 || fabs(accelerometerData->milligYValue) > 2300 || fabs(accelerometerData->milligZValue) > 2300) {
        appendStringCRLF(outputStream, "SHOCK !");
        adxl345_printAccelerometerDataListHeader(outputStream);
        adxl345_debugMainRegisterAcceleratorData(outputStream, accelerometerData->xRawLowValue, accelerometerData->xRawHighValue, accelerometerData->xRawValue, accelerometerData->milligXValue, "X");
        adxl345_debugMainRegisterAcceleratorData(outputStream, accelerometerData->yRawLowValue, accelerometerData->yRawHighValue, accelerometerData->yRawValue, accelerometerData->milligYValue, "Y");
        adxl345_debugMainRegisterAcceleratorData(outputStream, accelerometerData->zRawLowValue, accelerometerData->zRawHighValue, accelerometerData->zRawValue, accelerometerData->milligZValue, "Z");

        appendTableHeaderSeparatorLine(outputStream);
    }
}
*/
