#include <stdlib.h>

#include "serial.h"
#include "serialOutputStream.h"
#include "serialInputInterrupt.h"
#include "serialLink.h"
#include "serialLinkList.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

SerialLink* openSerialLink( 
        StreamLink* streamLink,
        const char* serialName, 
        Buffer* inputBuffer,
        char (*inputBufferArray)[],
        unsigned char inputBufferLength,
        Buffer* outputBuffer,
        char (*outputBufferArray)[],
        unsigned char outputBufferLength,
        OutputStream* outputStream,
        enum SerialPort serialPort,
        long speed) {
    SerialLink* result = addSerialLink();
    result->speed = speed;
    result->name = serialName;
    result->serialPort = serialPort;
    result->streamLink = streamLink;

    // Provide to the Hardware Uart the needed Buffer
    initSerialInputBuffer(inputBuffer, serialPort);

    // Initializes the Hardware uart output
    initSerialOutputStream(outputStream, serialPort);

    // Initializes All Buffers / Memory
    initStreamLink(streamLink,
                    serialName,
                    inputBuffer,
                    inputBufferArray,
                    inputBufferLength,
                    outputBuffer,
                    outputBufferArray,
                    outputBufferLength,
                    outputStream,
                    speed);

    return result;
}

void closeSerialLink(StreamLink* streamLink) {
    OutputStream* outputStream = streamLink->outputStream;
    if (outputStream != NULL) {
        outputStream->closeOutputStream(outputStream);
    }
}
