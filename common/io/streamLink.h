#ifndef STREAM_LINK_H
#define STREAM_LINK_H

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"

/**
 * Structure to manage an inputStream and a outputStream with both FIFO buffers.
 *        ____________________
 *       |                   |
 *       | (I2C/UART/LOCAL)  |
 *		| By interruption   |
 *       |___________________|
 *              |
 *  ____________|______________
 * |            v              |
 * | inputBuffer->outputStream |
 * |---------------------------|
 * |      inputBuffer          |
 * |---------------------------|
 * |  inputBuffer->inputStream |
 * |____________^______________|
 *              |
 *          READ DATA
 *       HANDLE TREATMENT
 *          WRITE DATA
 *  ____________|______________
 * |            v              |Output
 * | outputBuffer->outputStream|
 * |---------------------------|
 * |      outputBuffer         |
 * |-------------------------- |
 * | outputBuffer->inputStream |
 * |___________________________|
 *              |
 *              | (IOUtils.copyInputToOutputStream(
 *              |      outputBuffer->inputStream, outputStream)
 *        ______|_______
 *       |      v       |
 *       | OutputStream |
 *       | (I2C/UART)   |
 *       |______________|
 */
typedef struct {
    /** A FIFO buffer for the input stream. */
    Buffer* inputBuffer;
    /** A FIFO buffer for the output stream. */
    Buffer* outputBuffer;
    /** The output stream arround. */
    OutputStream* outputStream;
}
StreamLink;

/**
 * Init a stream link structure.
 */
void initStreamLink(StreamLink* streamLink,
        char* streamName,
        Buffer* inputBuffer,
		char (*inputBufferArrayPointer)[],
		unsigned char inputBufferLength,
        Buffer* outputBuffer,
		char (*outputBufferArrayPointer)[],
		unsigned char outputBufferLength,
        OutputStream* outputStream);

#endif
