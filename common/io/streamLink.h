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
 *        | By interruption   |
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
    /** The output stream around. */
    OutputStream* outputStream;
}
StreamLink;

/**
 * Init a stream link structure.
 * @param streamLink the structure which stores attributes of stream link
 * @param inputBuffer the buffer which use the input
 * @param inputBufferArrayPointer the array used by the input buffer
 * @param inputBufferLenght the length of the input buffer
 * @param outputBuffer the buffer which use the output
 * @param outputBufferArrayPointer the array used by the output buffer
 * @param outputBufferLenght the length of the output buffer
 * @param outputStream the physical outputStream (Ex : serial)
 * @param param a parameter to be used to open the right material (for example : speed)
 */
void initStreamLink(StreamLink* streamLink,
        const char* streamName,
        Buffer* inputBuffer,
        unsigned char (*inputBufferArrayPointer)[],
        unsigned int inputBufferLength,
        Buffer* outputBuffer,
        unsigned char (*outputBufferArrayPointer)[],
        unsigned int outputBufferLength,
        OutputStream* outputStream,
        int param);

#endif
