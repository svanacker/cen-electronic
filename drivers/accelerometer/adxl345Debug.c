#include "adxl345Debug.h"
#include "adxl345Register.h"

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
void adxl345_printRegisterListHeader(OutputStream* outputStream) {
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "#Reg", ADXL345_DEBUG_REG_COLUMN_LENGTH);
	appendStringHeader(outputStream, "#Reg Hex", ADXL345_DEBUG_REG_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Reg Name", ADXL345_DEBUG_REG_NAME_COLUMN_LENGTH); 
	appendStringHeader(outputStream, "R/W", ADXL345_DEBUG_REG_RW_COLUMN_LENGTH);       
    appendStringHeader(outputStream, "Dec Value", ADXL345_DEBUG_REG_VALUE_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Hex Value", ADXL345_DEBUG_REG_VALUE_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Bin Value", ADXL345_DEBUG_REG_VALUE_BIN_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, 0);
	appendTableHeaderSeparatorLine(outputStream);
}

/**
 * Private
 * @param i2cBusConnection
 */
void adxl345_debugMainRegister(OutputStream* outputStream, I2cBusConnection* i2cBusConnection, unsigned char reg, const char* regName, const char* rw) {
    unsigned char value = adxl345_read8(i2cBusConnection, reg);
	appendDecTableData(outputStream, reg, ADXL345_DEBUG_REG_COLUMN_LENGTH);
	appendHex2TableData(outputStream, reg, ADXL345_DEBUG_REG_HEX_COLUMN_LENGTH);
	appendStringTableData(outputStream, regName, ADXL345_DEBUG_REG_NAME_COLUMN_LENGTH);
	appendStringTableData(outputStream, rw, ADXL345_DEBUG_REG_RW_COLUMN_LENGTH);
    appendDecTableData(outputStream, value, ADXL345_DEBUG_REG_VALUE_DEC_COLUMN_LENGTH);
    appendHex2TableData(outputStream, value, ADXL345_DEBUG_REG_VALUE_HEX_COLUMN_LENGTH);
	appendBinary8TableData(outputStream, value, 4, ADXL345_DEBUG_REG_VALUE_BIN_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, 0);
}

void adxl345_debugMainRegisterList(OutputStream* outputStream, Accelerometer* accelerometer) {
    I2cBusConnection* i2cBusConnection = (I2cBusConnection*) accelerometer->object;
    adxl345_printRegisterListHeader(outputStream);
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_DEVID, "REG_DEVID", "R");
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_THRESH_TAP, "REG_THRESH_TAP", "R/W");
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_OFSX, "REG_OFSX", "R/W");
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_OFSY, "REG_OFSY", "R/W");
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_OFSZ, "REG_OFSZ", "R/W");
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_DUR, "REG_DUR", "R/W");
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_LATENT, "REG_LATENT", "R/W");
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_WINDOW, "REG_WINDOW", "R/W");
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_THRESH_ACT, "REG_THRESH_ACT", "R/W");
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_THRESH_INACT, "REG_THRESH_INACT", "R/W");
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_TIME_INACT, "REG_TIME_INACT", "R/W");
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_ACT_INACT_CTL, "REG_ACT_INACT_CTL", "R/W");
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_THRESH_FF, "REG_THRESH_FF", "R/W");
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_TIME_FF, "REG_TIME_FF", "R/W");

    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_TAP_AXES, "REG_TAP_AXES", "R/W");
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_ACT_TAP_STATUS, "REG_ACT_TAP_STATUS", "R");
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_BW_RATE, "REG_BW_RATE", "R/W");
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_POWER_CTL, "REG_POWER_CTL", "R/W");
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_INT_ENABLE, "REG_INT_ENABLE", "R/W");
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_INT_MAP, "REG_INT_MAP", "R/W");
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_INT_SOURCE, "REG_INT_SOURCE", "R/W");
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_DATA_FORMAT, "REG_DATA_FORMAT", "R/W");

    appendTableHeaderSeparatorLine(outputStream);
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_DATAX0, "REG_DATAX0", "R");
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_DATAX1, "REG_DATAX1", "R");    
    appendTableHeaderSeparatorLine(outputStream);
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_DATAY0, "REG_DATAY0", "R");
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_DATAY1, "REG_DATAY1", "R");
    appendTableHeaderSeparatorLine(outputStream);
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_DATAZ0, "REG_DATAZ0", "R");
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_DATAZ1, "REG_DATAZ1", "R");
    appendTableHeaderSeparatorLine(outputStream);
    
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_FIFO_CTL, "REG_FIFO_CTL", "R/W");
    adxl345_debugMainRegister(outputStream, i2cBusConnection, REG_FIFO_STATUS, "REG_FIFO_STATUS", "R");

    appendTableHeaderSeparatorLine(outputStream);
}

// DEBUG VALUES

/**
* Private.
*/
void adxl345_printAccelerometerDataListHeader(OutputStream* outputStream) {
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "X/Y/Z", ADXL345_DEBUG_REG_COLUMN_LENGTH);
	appendStringHeader(outputStream, "HIGH", ADXL345_DEBUG_REG_VALUE_HEX_COLUMN_LENGTH);    
	appendStringHeader(outputStream, "LOW", ADXL345_DEBUG_REG_VALUE_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Hex Value", ADXL345_DEBUG_REG_VALUE_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Dec Value", ADXL345_DEBUG_REG_VALUE_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Acc Value (mg)", ADXL345_DEBUG_REG_VALUE_MG_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, 0);
	appendTableHeaderSeparatorLine(outputStream);
}

/**
 * Private
 * @param i2cBusConnection
 */
void adxl345_debugMainRegisterAcceleratorData(OutputStream* outputStream, unsigned char low, unsigned char high, int value, float mgValue, const char* regName) {
	appendStringTableData(outputStream, regName, ADXL345_DEBUG_REG_COLUMN_LENGTH);
    appendHex2TableData(outputStream, high, ADXL345_DEBUG_REG_HEX_COLUMN_LENGTH);
    appendHex2TableData(outputStream, low, ADXL345_DEBUG_REG_HEX_COLUMN_LENGTH);
	appendHex4TableData(outputStream, value, ADXL345_DEBUG_REG_HEX_COLUMN_LENGTH);
	appendDecTableData(outputStream, value, ADXL345_DEBUG_REG_VALUE_DEC_COLUMN_LENGTH);
    appendDecfTableData(outputStream, mgValue, ADXL345_DEBUG_REG_VALUE_MG_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, 0);
}

void adxl345_debugValueRegisterList(OutputStream* outputStream, Accelerometer* accelerometer) {
    AccelerometerData* accelerometerData = accelerometer->accelerometerData;
    adxl345_printAccelerometerDataListHeader(outputStream);
    adxl345_debugMainRegisterAcceleratorData(outputStream, accelerometerData->xRawLowValue, accelerometerData->xRawHighValue, accelerometerData->xRawValue, accelerometerData->milligXValue, "X");
    adxl345_debugMainRegisterAcceleratorData(outputStream, accelerometerData->yRawLowValue, accelerometerData->yRawHighValue, accelerometerData->yRawValue, accelerometerData->milligYValue, "Y");
    adxl345_debugMainRegisterAcceleratorData(outputStream, accelerometerData->zRawLowValue, accelerometerData->zRawHighValue, accelerometerData->zRawValue, accelerometerData->milligZValue, "Z");

    appendTableHeaderSeparatorLine(outputStream);
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
