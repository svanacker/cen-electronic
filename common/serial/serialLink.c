#include <stdlib.h>

#include "serial.h"
#include "serialOutputStream.h"
#include "serialInputInterrupt.h"
#include "serialLink.h"

#include "../../common/commons.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

void openSerialLink(StreamLink* streamLink,
        Buffer* inputBuffer,
        char (*inputBufferArray)[],
        unsigned char inputBufferLength,
        Buffer* outputBuffer,
        char (*outputBufferArray)[],
        unsigned char outputBufferLength,
        OutputStream* outputStream,
        int serialPortIndex,
        long speed) {
    // Provide to the Hardware Uart the needed Buffer
    appendStringAndDec(getOutputStreamLogger(DEBUG), "\ninitSerialInputBuffer:", serialPortIndex);
    initSerialInputBuffer(inputBuffer, serialPortIndex);

    // Initializes the Hardware uart output
    appendStringAndDec(getOutputStreamLogger(DEBUG), "\ninitSerialOutputStream:", serialPortIndex);
    initSerialOutputStream(outputStream, serialPortIndex);

    // Initializes All Buffers / Memory
    appendStringAndDec(getOutputStreamLogger(DEBUG), "\ninitStreamLink", serialPortIndex);
    initStreamLink(streamLink,
                    "Serial",
                    inputBuffer,
                    inputBufferArray,
                    inputBufferLength,
                    outputBuffer,
                    outputBufferArray,
                    outputBufferLength,
                    outputStream,
                    speed);
}

void closeSerialLink(StreamLink* streamLink) {
    OutputStream* outputStream = streamLink->outputStream;
    if (outputStream != NULL) {
        outputStream->closeOutputStream(outputStream);
    }
}
