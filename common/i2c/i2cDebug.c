#include "i2cDebug.h"

#include <stdlib.h>
#include <stdbool.h>

#include "i2cBusList.h"

#include "../../common/error/error.h"

#include "../../common/io/bufferDebug.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/binaryPrintWriter.h"

#include "../../common/log/logger.h"

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
    unsigned char(*debugI2cInputBufferArray)[],
    unsigned int debugI2cInputBufferLength,
    Buffer* aDebugI2cOutputBuffer,
    unsigned char(*debugI2cOutputBufferArray)[],
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
    OutputStream* outputStreamLogger = getInfoOutputStreamLogger();

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

void printI2cBus(OutputStream* outputStream, I2cBus* i2cBus) {
    if (!checkI2cBusNotNull(i2cBus)) {
        return;
    }

    // Type
    appendString(outputStream, "I2C : type=");
    if (i2cBus->busType == I2C_BUS_TYPE_UNKNOWN) {
        appendString(outputStream, " !! UNKNOWN !!");    
    }
    if (i2cBus->busType == I2C_BUS_TYPE_MASTER) {
        appendString(outputStream, "MASTER");    
    }
    else if (i2cBus->busType == I2C_BUS_TYPE_MASTER) {
        appendString(outputStream, "SLAVE"); 
    }
    else {
        appendString(outputStream, "??");
    }

    // PortIndex
    appendStringAndDec(outputStream, ", portIndex=I2C_BUS_PORT_", i2cBus->port);

    // Config
    appendString(outputStream, ", CONF=");
    appendBinary16(outputStream, i2cBus->config, 4);
}

void printI2cBusConnection(OutputStream* outputStream, I2cBusConnection* i2cBusConnection) {
    if (!checkI2cBusConnectionNotNull(i2cBusConnection)) {
        return;
    }

    // Address
    appendStringAndDec(outputStream, "I2cBusConnection : i2cAddress=", i2cBusConnection->i2cAddress);
    appendString(outputStream, ", opened=");

    // Opened
    appendBool(outputStream, i2cBusConnection->opened);
}

const char* getI2cBusTypeAsString(enum I2cBusType i2cBusType) {
	switch (i2cBusType) {
		case I2C_BUS_TYPE_MASTER: return "I2C_MASTER";
		case I2C_BUS_TYPE_SLAVE: return "I2C_SLAVE";
		case I2C_BUS_TYPE_UNKNOWN: return "I2C_UNKOWN";
		default: return "I2C_???";
	}
	return "I2C_???";
}

const char* getI2cPortAsString(enum I2cPort i2cPort) {
	switch (i2cPort) {
		case I2C_BUS_PORT_1: return "I2C_BUS_PORT_1";
		case I2C_BUS_PORT_2: return "I2C_BUS_PORT_2";
		case I2C_BUS_PORT_3: return "I2C_BUS_PORT_3";
		case I2C_BUS_PORT_4: return "I2C_BUS_PORT_4";
		default: return "I2C_PORT_??";
	}
	return "I2C_PORT_??";
}
