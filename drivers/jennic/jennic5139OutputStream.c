#include <stdlib.h>

#include "jennic5139OutputStream.h"

#include "../../common/io/buffer.h"

#include "jennic5139Driver.h"

/**
 * OUTPUT STREAM INTERFACE FOR JENNIC 5139
 * Output is buffered because we send more efficiently the data
 */

/**
 * @private
 */
Buffer* _jennic5139GetOutputBuffer(OutputStream* outputStream) {
    Buffer* result = (Buffer*) outputStream->object;

    return result;
}

/**
 * @private
 */
void _jennic5139OpenOutputStream(OutputStream* outputStream, int param1) {
    // Initialization is done BEFORE
}

/**
 * @private
 */
void _jennic5139CloseOutputStream(OutputStream* outputStream) {
	// DO NOT END
}

/**
 * @private
 * We don't write directly the char, because it's more efficient
 * to wait the end of data to send a array in zigbee
 */
void _writeCharJennic5139(OutputStream* outputStream, char c) {
    Buffer* buffer = _jennic5139GetOutputBuffer(outputStream);
    bufferWriteChar(buffer, c);
}

/**
 * @private
 * We flush the buffer (more efficient)
 */
void _flushJennic5139(OutputStream* outputStream) {
    Buffer* buffer = _jennic5139GetOutputBuffer(outputStream);
    char* macAddress = buffer->name;
	sendJennic5138DataBuffer(&(buffer->inputStream), macAddress, DATA_TRANSMISSION_FLAG_MASK_ACK);
}

void initZigbeeOutputStream(OutputStream* outputStream,
        						Buffer* jennic5139Buffer,
        						char* jennicAddress) {
    outputStream->openOutputStream = _jennic5139OpenOutputStream;
    outputStream->closeOutputStream = _jennic5139CloseOutputStream;
    outputStream->writeChar = _writeCharJennic5139;
    outputStream->flush = _flushJennic5139;
    outputStream->object = (int*) jennic5139Buffer;
	// Tips: store the address into the name
	jennic5139Buffer->name = jennicAddress;
    _jennic5139OpenOutputStream(outputStream, NULL);
}
