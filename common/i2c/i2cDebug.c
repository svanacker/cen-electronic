#include "i2cDebug.h"

#include <stdbool.h>
#include <stdlib.h>

#include "i2cCommon.h"
#include "i2cBusList.h"

#include "../../common/commons.h"

#include "../../common/io/buffer.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#include "../../common/log/logHandler.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

static Buffer* debugI2cInputBuffer;
static Buffer* debugI2cOutputBuffer;
static bool debugI2cEnabled;

bool getDebugI2cEnabled() {
    return debugI2cEnabled;
}

void setDebugI2cEnabled(bool enabled) {
    debugI2cEnabled = enabled;
}

void initI2CDebugBuffers(Buffer* aDebugI2cInputBuffer,
                         char (*debugI2cInputBufferArray)[],
                         unsigned int debugI2cInputBufferLength,
                         Buffer* aDebugI2cOutputBuffer,
                         char (*debugI2cOutputBufferArray)[],
                         unsigned int debugI2cOutputBufferLength
) {
    debugI2cInputBuffer = aDebugI2cInputBuffer;
    debugI2cOutputBuffer = aDebugI2cOutputBuffer;
    // Init Buffers
    initBuffer(debugI2cInputBuffer, debugI2cInputBufferArray, debugI2cInputBufferLength, "I2C IN DBG", IN_AS_STRING);
    initBuffer(debugI2cOutputBuffer, debugI2cOutputBufferArray, debugI2cOutputBufferLength, "I2C OUT DBG", OUT_AS_STRING);
    debugI2cEnabled = true;
}

void appendI2cDebugInputChar(unsigned char debugValue) {
    if (!debugI2cEnabled) {
        return;
    }
    if (debugI2cInputBuffer != NULL) {
        bufferWriteChar(debugI2cInputBuffer, debugValue);
    }
}

void appendI2cDebugOutputChar(unsigned char debugValue) {
    if (!debugI2cEnabled) {
        return;
    }
    if (debugI2cInputBuffer != NULL) {
        bufferWriteChar(debugI2cOutputBuffer, debugValue);
    }
}

void printI2cDebugBuffers() {
    OutputStream* outputStreamLogger = getAlwaysOutputStreamLogger();

    println(outputStreamLogger);
    appendString(outputStreamLogger, "I2C:Is Enabled:");
    appendBool(outputStreamLogger, debugI2cEnabled);
    println(outputStreamLogger);
   
    if (debugI2cInputBuffer != NULL) {
        appendString(outputStreamLogger, "I2C:In:");
        printDebugBuffer(outputStreamLogger, debugI2cInputBuffer);
        println(outputStreamLogger);
    }
    if (debugI2cOutputBuffer != NULL) {
        appendString(outputStreamLogger, "I2C:Out:");
        printDebugBuffer(outputStreamLogger, debugI2cOutputBuffer);
        println(outputStreamLogger);
    }
}

// I2C BUS LIST

#define I2C_DEBUG_INDEX_COLUMN_LENGTH		   4
#define I2C_DEBUG_BUS_TYPE_COLUMN_LENGTH      15
#define I2C_DEBUG_PORT_COLUMN_LENGTH		  15
#define I2C_DEBUG_INITIALIZED_COLUMN_LENGTH   8
#define I2C_DEBUG_CONFIG_COLUMN_LENGTH        8
#define I2C_DEBUG_LAST_COLUMN_LENGTH          48


/**
* @private
*/
void printI2cBusListTableHeader(OutputStream* outputStream) {
	println(outputStream);

	// Table Header
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "Idx", I2C_DEBUG_INDEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "busType", I2C_DEBUG_BUS_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "port", I2C_DEBUG_PORT_COLUMN_LENGTH);
	appendStringHeader(outputStream, "init ?", I2C_DEBUG_INITIALIZED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "config", I2C_DEBUG_CONFIG_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, I2C_DEBUG_LAST_COLUMN_LENGTH);
	appendTableSeparator(outputStream);
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
}

void printI2cBusList(OutputStream* outputStream) {
	printI2cBusListTableHeader(outputStream);
	int i;
	for (i = 0; i < getI2cBusListCount(); i++) {
		I2cBus* i2cBus = getI2cBusByIndex(i);
		appendDecTableData(outputStream, i, I2C_DEBUG_INDEX_COLUMN_LENGTH);
		const char* i2cBusTypeAsString = getI2cBusTypeAsString(i2cBus->busType);
		appendStringTableData(outputStream, i2cBusTypeAsString, I2C_DEBUG_BUS_TYPE_COLUMN_LENGTH);
		const char* i2cPortAsString = getI2cPortAsString(i2cBus->port);
		appendStringTableData(outputStream, i2cPortAsString, I2C_DEBUG_PORT_COLUMN_LENGTH);
		appendDecTableData(outputStream, i2cBus->initialized, I2C_DEBUG_INITIALIZED_COLUMN_LENGTH);
		appendHex2TableData(outputStream, i2cBus->config, I2C_DEBUG_CONFIG_COLUMN_LENGTH);
		appendEndOfTableColumn(outputStream, I2C_DEBUG_LAST_COLUMN_LENGTH);
	}
	appendTableHeaderSeparatorLine(outputStream);
}
