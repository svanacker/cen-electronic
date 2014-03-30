#ifndef SERIAL_LINK_H
#define SERIAL_LINK_H

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/streamLink.h"

/**
 * Opens a serial link with (input->inputBuffer->outputBuffer->output) wrapper.
 * @param streamLink pointer on non-initialized structure
 * @param inputStream pointer on non-initialized structure
 * @param inputBuffer the buffer for inputStream
 * @param outputStream pointer on non-initialized structure
 * @param outputBuffer the buffer for outputStream
 * @param serialPortIndex the index of the port (SERIAL_PORT_INDEX_1 / SERIAL_PORT_INDEX_2)
 */
void openSerialLink(StreamLink* streamLink,
        Buffer* inputBuffer,
        char (*inputBufferArrayPointer)[],
        unsigned char inputBufferLength,
        Buffer* outputBuffer,
        char (*outputBufferArrayPointer)[],
        unsigned char outputBufferLength,
        OutputStream* outputStream,
        int serialPortIndex,
        int speed);

/**
 * Closes the stream link.
 * @param streamLink the serial link we want to close.
 */
void closeSerialLink(StreamLink* streamLink);

#endif
