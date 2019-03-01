#include "pca9685Debug.h"
#include "pca9685.h"

#include "../../common/log/logger.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

// DEBUG

#define PCA9685_DEBUG_REG_COLUMN_LENGTH	             10
#define PCA9685_DEBUG_REG_HEX_COLUMN_LENGTH	         10
#define PCA9685_DEBUG_REG_NAME_COLUMN_LENGTH	     15
#define PCA9685_DEBUG_REG_VALUE_DEC_COLUMN_LENGTH	 10
#define PCA9685_DEBUG_REG_VALUE_HEX_COLUMN_LENGTH	 10
#define PCA9685_DEBUG_REG_VALUE_BIN_COLUMN_LENGTH	 15

/**
* Private.
*/
void pca9685_printListHeader(OutputStream* outputStream) {
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "#Reg", PCA9685_DEBUG_REG_COLUMN_LENGTH);
	appendStringHeader(outputStream, "#Reg Hex", PCA9685_DEBUG_REG_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Reg Name", PCA9685_DEBUG_REG_NAME_COLUMN_LENGTH);   
    appendStringHeader(outputStream, "Dec Value", PCA9685_DEBUG_REG_VALUE_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Hex Value", PCA9685_DEBUG_REG_VALUE_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Bin Value", PCA9685_DEBUG_REG_VALUE_BIN_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, 0);
	appendTableHeaderSeparatorLine(outputStream);
}

/**
 * Private
 * @param i2cBusConnection
 */
void pca9685_debugMainRegister(OutputStream* outputStream, I2cBusConnection* i2cBusConnection, unsigned char reg, const char* regName) {
    unsigned value = pca9685_read8(i2cBusConnection, reg);
	appendDecTableData(outputStream, reg, PCA9685_DEBUG_REG_COLUMN_LENGTH);
	appendHex4TableData(outputStream, reg, PCA9685_DEBUG_REG_HEX_COLUMN_LENGTH);
	appendStringTableData(outputStream, regName, PCA9685_DEBUG_REG_NAME_COLUMN_LENGTH);
    appendDecTableData(outputStream, value, PCA9685_DEBUG_REG_VALUE_DEC_COLUMN_LENGTH);
    appendHex2TableData(outputStream, value, PCA9685_DEBUG_REG_VALUE_HEX_COLUMN_LENGTH);
	appendBinary8TableData(outputStream, value, 4, PCA9685_DEBUG_REG_VALUE_BIN_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, 0);
}

void pca9685_debugMainRegisterList(OutputStream* outputStream, I2cBusConnection* i2cBusConnection) {
    pca9685_printListHeader(outputStream);
    pca9685_debugMainRegister(outputStream, i2cBusConnection, PCA9685_MODE1, "MODE1");
    pca9685_debugMainRegister(outputStream, i2cBusConnection, PCA9685_PRESCALE, "PRESCALER");
    // BUG WITH MODE 2 READ : pca9685_debugMainRegister(outputStream, i2cBusConnection, PCA9685_MODE2, "MODE2");
    // pca9685_debugMainRegister(outputStream, i2cBusConnection, PCA9685_MODE2, "MODE2");
    pca9685_debugMainRegister(outputStream, i2cBusConnection, PCA9685_SUBADR1, "SUBADR1");
    pca9685_debugMainRegister(outputStream, i2cBusConnection, PCA9685_SUBADR2, "SUBADR2");
    pca9685_debugMainRegister(outputStream, i2cBusConnection, PCA9685_SUBADR3, "SUBADR3");
    pca9685_debugMainRegister(outputStream, i2cBusConnection, PCA9885_ALLCALLADR, "ALLCALLADR");

    // LED 0
    pca9685_debugMainRegister(outputStream, i2cBusConnection, LED0_ON_L, "LED0_ON_L");
    pca9685_debugMainRegister(outputStream, i2cBusConnection, LED0_ON_H, "LED0_ON_H");
    pca9685_debugMainRegister(outputStream, i2cBusConnection, LED0_OFF_L, "LED0_OFF_L");
    pca9685_debugMainRegister(outputStream, i2cBusConnection, LED0_OFF_H, "LED0_OFF_H");    

    // LED 1
    pca9685_debugMainRegister(outputStream, i2cBusConnection, LED0_ON_L + 4, "LED1_ON_L");
    pca9685_debugMainRegister(outputStream, i2cBusConnection, LED0_ON_H + 4, "LED1_ON_H");
    pca9685_debugMainRegister(outputStream, i2cBusConnection, LED0_OFF_L + 4, "LED1_OFF_L");
    pca9685_debugMainRegister(outputStream, i2cBusConnection, LED0_OFF_H + 4, "LED1_OFF_H");    
    appendTableHeaderSeparatorLine(outputStream);
}
