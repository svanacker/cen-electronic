#include "bufferedOutputStream.h"
#include "buffer.h"
#include "outputStream.h"
#include "ioUtils.h"

/**
* @private
*/
bufferStruct* getBuffer(int* stream) {
	bufferedOutputStreamStruct* bufferedOutputStream = (bufferedOutputStreamStruct*) stream;
	bufferStruct* result = bufferedOutputStream->buffer;
	return result;
}

/**
* @private
*/
outputStreamStruct* getEncapsulatedOutputStream(int* stream) {
	bufferedOutputStreamStruct* bufferedOutputStream = (bufferedOutputStreamStruct*) stream;
	outputStreamStruct* result = bufferedOutputStream->encapsulatedOutputStream;
	return result;
}

/**
* @private
*/
outputStreamStruct* getStreamInterface(int* stream) {
	bufferedOutputStreamStruct* bufferedOutputStream = (bufferedOutputStreamStruct*) stream;
	outputStreamStruct* result = bufferedOutputStream->streamInterface;
	return result;
}

void bufferedFlush(int* stream) {
	bufferStruct* buffer = getBuffer(stream);
	outputStreamStruct* encapsulatedOutputStream = ;

	copyInputToOutputStream(buffer->inputStream, 
							 outputStreamStruct* outputStream,
							 filterCharFunction* filterChar
}

void writeBufferedChar(int* stream, char c) {
	bufferStruct* buffer = getBuffer(stream);
	bufferWriteChar(buffer, c);
}

void initBufferedOutputStream(bufferedOutputStreamStruct* bufferedOutputStream,
							 outputStreamStruct* encapsulatedOutputStream,
							 outputStreamStruct* streamInterface,
							 bufferStruct* buffer) {
	bufferedOutputStream->encapsulatedOutputStream = encapsulatedOutputStream;
	bufferedOutputStream->streamInterface = streamInterface;
	bufferedOutputStream->buffer = buffer;
	bufferedOutputStream->streamInterface->openOutputStream = encapsulatedOutputStream->openOutputStream;
	bufferedOutputStream->streamInterface->closeOutputStream = encapsulatedOutputStream->closeOutputStream;
	bufferedOutputStream->streamInterface->writeChar = writeBufferedChar;
	bufferedOutputStream->streamInterface->flush = bufferedFlush;
}
