#include "i2cBusListDebug.h"

#include <stdbool.h>
#include <stdlib.h>

#include "i2cCommon.h"
#include "i2cDebug.h"
#include "i2cBusList.h"
#include "i2cBusConnectionList.h"

#include "../../common/commons.h"

#include "../../common/error/error.h"

#include "../../common/io/buffer.h"
#include "../../common/io/bufferDebug.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#include "../../common/log/logHandler.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

// I2C BUS LIST

#define I2C_BUS_LIST_INDEX_COLUMN_LENGTH		   4
#define I2C_BUS_LIST_BUS_TYPE_COLUMN_LENGTH       15
#define I2C_BUS_LIST_PORT_COLUMN_LENGTH		      15
#define I2C_BUS_LIST_INITIALIZED_COLUMN_LENGTH     8
#define I2C_BUS_LIST_ERROR_COLUMN_LENGTH          12
#define I2C_BUS_LIST_CONFIG_COLUMN_LENGTH          8
#define I2C_BUS_LIST_LAST_COLUMN_LENGTH           20


/**
* @private
*/
void printI2cBusListTableHeader(OutputStream* outputStream) {
	println(outputStream);

	// Table Header
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "Idx", I2C_BUS_LIST_INDEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "busType", I2C_BUS_LIST_BUS_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "port", I2C_BUS_LIST_PORT_COLUMN_LENGTH);
	appendStringHeader(outputStream, "init ?", I2C_BUS_LIST_INITIALIZED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "error (Hex)", I2C_BUS_LIST_ERROR_COLUMN_LENGTH);
	appendStringHeader(outputStream, "config", I2C_BUS_LIST_CONFIG_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, I2C_BUS_LIST_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);
}

void printI2cBusList(OutputStream* outputStream) {
	printI2cBusListTableHeader(outputStream);
	int i;
	for (i = 0; i < getI2cBusListCount(); i++) {
		I2cBus* i2cBus = getI2cBusByIndex(i);
		appendDecTableData(outputStream, i, I2C_BUS_LIST_INDEX_COLUMN_LENGTH);
		const char* i2cBusTypeAsString = getI2cBusTypeAsString(i2cBus->busType);
		appendStringTableData(outputStream, i2cBusTypeAsString, I2C_BUS_LIST_BUS_TYPE_COLUMN_LENGTH);
		const char* i2cPortAsString = getI2cPortAsString(i2cBus->port);
		appendStringTableData(outputStream, i2cPortAsString, I2C_BUS_LIST_PORT_COLUMN_LENGTH);
		appendDecTableData(outputStream, i2cBus->initialized, I2C_BUS_LIST_INITIALIZED_COLUMN_LENGTH);
        if (i2cBus->error == ERROR_NONE) {
    		appendStringTableData(outputStream, "NONE", I2C_BUS_LIST_ERROR_COLUMN_LENGTH);
        }
        else {
    		appendHex4TableData(outputStream, i2cBus->error, I2C_BUS_LIST_ERROR_COLUMN_LENGTH);
        }
		appendHex2TableData(outputStream, i2cBus->config, I2C_BUS_LIST_CONFIG_COLUMN_LENGTH);
		appendEndOfTableColumn(outputStream, I2C_BUS_LIST_LAST_COLUMN_LENGTH);
	}
	appendTableHeaderSeparatorLine(outputStream);
}
