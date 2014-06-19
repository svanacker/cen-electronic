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

Buffer* getDebugI2cInputBuffer() {
    return debugI2cInputBuffer;
}

Buffer* getDebugI2cOutputBuffer() {
    return debugI2cOutputBuffer;
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
    initBuffer(debugI2cInputBuffer, debugI2cInputBufferArray, debugI2cInputBufferLength, "I2C DBG", IN_AS_STRING);
    initBuffer(debugI2cOutputBuffer, debugI2cOutputBufferArray, debugI2cOutputBufferLength, "I2C DBG", OUT_AS_STRING);
}

void printI2cDebugBuffers() {
    OutputStream* outputStreamLogger = getOutputStreamLogger(INFO);
    if (debugI2cInputBuffer != NULL) {
        println(outputStreamLogger);
        appendString(outputStreamLogger, "I2C:In:");
        copyInputToOutputStream(getInputStream(debugI2cInputBuffer), getDebugOutputStreamLogger(), NULL, COPY_ALL);
    }
    if (debugI2cOutputBuffer != NULL) {
        println(outputStreamLogger);
        appendString(outputStreamLogger, "I2C:Out:");
        copyInputToOutputStream(getInputStream(debugI2cOutputBuffer), getDebugOutputStreamLogger(), NULL, COPY_ALL);
        println(outputStreamLogger);
    }
}
