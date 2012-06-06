#include <stdlib.h>

#include "serial.h"
#include "serialOutputStream.h"
#include "serialInputInterrupt.h"
#include "serialLink.h"

#include "../../common/commons.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"

void openSerialLink(StreamLink* streamLink,
        Buffer* inputBuffer,
		char (*inputBufferArrayPointer)[],
		unsigned char inputBufferLength,
        Buffer* outputBuffer,
		char (*outputBufferArrayPointer)[],
		unsigned char outputBufferLength,
        OutputStream* outputStream,
        int serialPortIndex) {
    initSerialInputBuffer(inputBuffer, serialPortIndex);
    initSerialOutputStream(outputStream, serialPortIndex);
    initStreamLink(streamLink, "Serial",
					inputBuffer,
					inputBufferArrayPointer,
					inputBufferLength,
					outputBuffer,
					outputBufferArrayPointer,
					outputBufferLength,
					outputStream);
}

void closeSerialLink(StreamLink* streamLink) {
    OutputStream* outputStream = streamLink->outputStream;
    if (outputStream != NULL) {
        outputStream->closeOutputStream(outputStream);
    }
}
