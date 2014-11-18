#include <stdbool.h>
#include <stdlib.h>

#include "../../common/commons.h"

#include "../../common/io/buffer.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/ioUtils.h"

#include "../../common/log/logHandler.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

static Buffer* debugI2cInputBuffer;
static Buffer* debugI2cOutputBuffer;
static bool debugI2cEnabled;

Buffer* getDebugI2cInputBuffer() {
    return debugI2cInputBuffer;
}

Buffer* getDebugI2cOutputBuffer() {
    return debugI2cOutputBuffer;
}

bool getDebugI2cEnabled() {
    return debugI2cEnabled;
}

void setDebugI2cEnabled(bool enabled) {
    debugI2cEnabled = enabled;
}

void initI2CDebugBuffers(Buffer* aDebugI2cInputBuffer,
                         char (*debugI2cInputBufferArray)[],
                         unsigned char debugI2cInputBufferLength,
                         Buffer* aDebugI2cOutputBuffer,
                         char (*debugI2cOutputBufferArray)[],
                         unsigned char debugI2cOutputBufferLength
) {
    debugI2cInputBuffer = aDebugI2cInputBuffer;
    debugI2cOutputBuffer = aDebugI2cOutputBuffer;
    // Init Buffers
    initBuffer(debugI2cInputBuffer, debugI2cInputBufferArray, debugI2cInputBufferLength, "I2C IN DBG", IN_AS_STRING);
    initBuffer(debugI2cOutputBuffer, debugI2cOutputBufferArray, debugI2cOutputBufferLength, "I2C OUT DBG", OUT_AS_STRING);
    debugI2cEnabled = true;
}

void printI2cDebugBuffers() {
    OutputStream* outputStreamLogger = getOutputStreamLogger(ALWAYS);

    println(outputStreamLogger);
    appendString(outputStreamLogger, "I2C:Is Enabled:");
    appendBool(outputStreamLogger, debugI2cEnabled);
    println(outputStreamLogger);
   
    if (debugI2cInputBuffer != NULL) {
        appendString(outputStreamLogger, "I2C:In:");
        copyInputToOutputStream(getInputStream(debugI2cInputBuffer), outputStreamLogger, NULL, COPY_ALL);
        println(outputStreamLogger);
    }
    if (debugI2cOutputBuffer != NULL) {
        appendString(outputStreamLogger, "I2C:Out:");
        copyInputToOutputStream(getInputStream(debugI2cOutputBuffer), outputStreamLogger, NULL, COPY_ALL);
        println(outputStreamLogger);
    }
}
