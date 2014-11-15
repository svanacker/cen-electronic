#include "bufferedOutputStream.h"
#include "buffer.h"
#include "outputStream.h"
#include "ioUtils.h"

/**
* @private
*/
Buffer* getBuffer(int* stream) {
    bufferedOutputStreamStruct* bufferedOutputStream = (bufferedOutputStreamStruct*) stream;
    Buffer* result = bufferedOutputStream->buffer;
    return result;
}

/**
* @private
*/
OutputStream* getEncapsulatedOutputStream(int* stream) {
    bufferedOutputStream* bufferedOutputStream = (bufferedOutputStreamStruct*) stream;
    OutputStream* result = bufferedOutputStream->encapsulatedOutputStream;
    return result;
}

/**
* @private
*/
OutputStream* getStreamInterface(int* stream) {
    bufferedOutputStreamStruct* bufferedOutputStream = (bufferedOutputStreamStruct*) stream;
    OutputStream* result = bufferedOutputStream->streamInterface;
    return result;
}

void bufferedFlush(int* stream) {
    Buffer* buffer = getBuffer(stream);
    OutputStream* encapsulatedOutputStream = ;

    copyInputToOutputStream(buffer->inputStream, 
                             outputStreamStruct* outputStream,
                             filterCharFunction* filterChar
}

void writeBufferedChar(int* stream, char c) {
    Buffer* buffer = getBuffer(stream);
    bufferWriteChar(buffer, c);
}

void initBufferedOutputStream(BufferedOutputStream* bufferedOutputStream,
                             OutputStream* encapsulatedOutputStream,
                             OutputStream* streamInterface,
                             Buffer* buffer) {
    bufferedOutputStream->encapsulatedOutputStream = encapsulatedOutputStream;
    bufferedOutputStream->streamInterface = streamInterface;
    bufferedOutputStream->buffer = buffer;
    bufferedOutputStream->streamInterface->openOutputStream = encapsulatedOutputStream->openOutputStream;
    bufferedOutputStream->streamInterface->closeOutputStream = encapsulatedOutputStream->closeOutputStream;
    bufferedOutputStream->streamInterface->writeChar = writeBufferedChar;
    bufferedOutputStream->streamInterface->flush = bufferedFlush;
}
