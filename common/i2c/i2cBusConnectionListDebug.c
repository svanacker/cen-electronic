#include "i2cBusConnectionListDebug.h"

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

// I2C BUS CONNECTION LIST

#define I2C_BUS_CONNECTION_LIST_INDEX_COLUMN_LENGTH		                 6
#define I2C_BUS_CONNECTION_ADDRESS_COLUMN_LENGTH                        20
#define I2C_BUS_CONNECTION_LIST_OPENED_COLUMN_LENGTH                    12
#define I2C_BUS_CONNECTION_LIST_CONNECTION_ERROR_COLUMN_LENGTH          12
#define I2C_BUS_CONNECTION_LIST_BUS_TYPE_COLUMN_LENGTH                  12
#define I2C_BUS_CONNECTION_LIST_PORT_COLUMN_LENGTH                      15
#define I2C_BUS_CONNECTION_LIST_BUS_ERROR_COLUMN_LENGTH                 12
#define I2C_BUS_CONNECTION_LIST_LAST_COLUMN_LENGTH                      8

/**
* @private
*/
void printI2cBusConnectionListTableHeader(OutputStream* outputStream) {
	println(outputStream);

	// Table Header
    // First Line
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "Idx", I2C_BUS_CONNECTION_LIST_INDEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Connection", I2C_BUS_CONNECTION_ADDRESS_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Connection", I2C_BUS_CONNECTION_LIST_OPENED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Connection", I2C_BUS_CONNECTION_LIST_CONNECTION_ERROR_COLUMN_LENGTH);
	appendStringHeader(outputStream, "bus", I2C_BUS_CONNECTION_LIST_BUS_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "bus", I2C_BUS_CONNECTION_LIST_PORT_COLUMN_LENGTH);
	appendStringHeader(outputStream, "bus", I2C_BUS_CONNECTION_LIST_BUS_ERROR_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, I2C_BUS_CONNECTION_LIST_LAST_COLUMN_LENGTH);

    // Second Line
	appendStringHeader(outputStream, "(Dec)", I2C_BUS_CONNECTION_LIST_INDEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "slaveAddress (Hex)", I2C_BUS_CONNECTION_ADDRESS_COLUMN_LENGTH);
	appendStringHeader(outputStream, "opened", I2C_BUS_CONNECTION_LIST_OPENED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Error (Hex)", I2C_BUS_CONNECTION_LIST_CONNECTION_ERROR_COLUMN_LENGTH);
    
	appendStringHeader(outputStream, "type", I2C_BUS_CONNECTION_LIST_BUS_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "port", I2C_BUS_CONNECTION_LIST_PORT_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Error (Hex)", I2C_BUS_CONNECTION_LIST_BUS_ERROR_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, I2C_BUS_CONNECTION_LIST_LAST_COLUMN_LENGTH);


	appendTableHeaderSeparatorLine(outputStream);
}

void printI2cBusConnectionList(OutputStream* outputStream) {
	printI2cBusConnectionListTableHeader(outputStream);
	int i;
	for (i = 0; i < getI2cBusConnectionListCount(); i++) {
		I2cBusConnection* i2cBusConnection = getI2cBusConnectionByIndex(i);
		I2cBus* i2cBus = i2cBusConnection->i2cBus;
		
		// Index
		appendDecTableData(outputStream, i, I2C_BUS_CONNECTION_LIST_INDEX_COLUMN_LENGTH);

		// Connection Address
        appendHex2TableData(outputStream, i2cBusConnection->i2cAddress, I2C_BUS_CONNECTION_ADDRESS_COLUMN_LENGTH);

		// Connection Opened
        appendBoolAsStringTableData(outputStream, i2cBusConnection->opened, I2C_BUS_CONNECTION_LIST_OPENED_COLUMN_LENGTH);
        
        // Connection Error if any
        if (i2cBusConnection->error == ERROR_NONE) {
    		appendStringTableData(outputStream, "NONE", I2C_BUS_CONNECTION_LIST_CONNECTION_ERROR_COLUMN_LENGTH);
        }
        else {
    		appendHex4TableData(outputStream, i2cBusConnection->error, I2C_BUS_CONNECTION_LIST_CONNECTION_ERROR_COLUMN_LENGTH);
        }
		
		// Bus Type
		const char* i2cBusTypeAsString = getI2cBusTypeAsString(i2cBus->busType);
		appendStringTableData(outputStream, i2cBusTypeAsString, I2C_BUS_CONNECTION_LIST_BUS_TYPE_COLUMN_LENGTH);
		
		// Bus Port
		const char* i2cPortAsString = getI2cPortAsString(i2cBus->port);
		appendStringTableData(outputStream, i2cPortAsString, I2C_BUS_CONNECTION_LIST_PORT_COLUMN_LENGTH);
                
        // Bus Error if any
        if (i2cBus->error == ERROR_NONE) {
    		appendStringTableData(outputStream, "NONE", I2C_BUS_CONNECTION_LIST_BUS_ERROR_COLUMN_LENGTH);
        }
        else {
    		appendHex4TableData(outputStream, i2cBusConnection->error, I2C_BUS_CONNECTION_LIST_BUS_ERROR_COLUMN_LENGTH);
        }

        
		appendEndOfTableColumn(outputStream, I2C_BUS_CONNECTION_LIST_LAST_COLUMN_LENGTH);
	}
	appendTableHeaderSeparatorLine(outputStream);
}
