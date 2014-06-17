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
        char (*inputBufferArrayPointer)[],
        unsigned char inputBufferLength,
        Buffer* outputBuffer,
        char (*outputBufferArrayPointer)[],
        unsigned char outputBufferLength,
        OutputStream* outputStream,
        int serialPortIndex,
        long speed) {
    if (serialPortIndex != 1) {
        appendStringAndDec(getOutputStreamLogger(ALWAYS), "\ninitSerialInputBuffer:", serialPortIndex);
    }
    initSerialInputBuffer(inputBuffer, serialPortIndex);

    if (serialPortIndex != 1) {
        appendStringAndDec(getOutputStreamLogger(ALWAYS), "\ninitSerialOutputStream:", serialPortIndex);
    }
    initSerialOutputStream(outputStream, serialPortIndex);
    
    if (serialPortIndex != 1) {
        appendStringAndDec(getOutputStreamLogger(ALWAYS), "\ninitStreamLink", serialPortIndex);
    }
    initStreamLink(streamLink, "Serial",
            inputBuffer,
            inputBufferArrayPointer,
            inputBufferLength,
            outputBuffer,
            outputBufferArrayPointer,
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
