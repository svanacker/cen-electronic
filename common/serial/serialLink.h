#ifndef SERIAL_LINK_H
#define SERIAL_LINK_H

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/streamLink.h"

#include "serial.h"

struct SerialLink;
typedef struct SerialLink SerialLink;

/**
 * Wrap a serial Link, which uses streamLink for buffering.
 */
struct SerialLink {
    /** The link with buffers ... */
    StreamLink* streamLink;
    /** The name of the serial. */
    const char* name;
    /** The port */
    enum SerialPort serialPort;
    /** The speed of the link. */
    long speed;
};

/**
 * Opens a serial link with (input->inputBuffer->outputBuffer->output) wrapper.
 * @param streamLink pointer on non-initialized structure
 * @param serialName the name of the serial Name
 * @param inputStream pointer on non-initialized structure
 * @param inputBuffer the buffer for inputStream
 * @param inputBufferArrayPointer the pointer on the array which stores the input values
 * @param inputBufferLength the length of the array which stores the serial input values
 * @param outputStream pointer on non-initialized structure
 * @param outputBuffer the buffer for outputStream
 * @param outputBufferArrayPointer the pointer on the array which stores the output values
 * @param outputBufferLength the length of the array which stores the serial output values
 * @param serialPortIndex the index of the port (SERIAL_PORT_INDEX_1 / SERIAL_PORT_INDEX_2)
 * @param speed the speed of RS232 in Bauds (Ex : 115200)
 */
SerialLink* openSerialLink(StreamLink* streamLink,
        const char* serialName,
        Buffer* inputBuffer,
        char (*inputBufferArrayPointer)[],
        unsigned char inputBufferLength,
        Buffer* outputBuffer,
        char (*outputBufferArrayPointer)[],
        unsigned char outputBufferLength,
        OutputStream* outputStream,
        enum SerialPort serialPort,
        long speed);

/**
 * Closes the stream link.
 * @param streamLink the serial link we want to close.
 */
void closeSerialLink(StreamLink* streamLink);

#endif
