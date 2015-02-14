#include "compositeOutputStream.h"

#include "outputStream.h"

#include <stdlib.h>

#include "../../common/error/error.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

// Help method

/**
 * @private
 */
CompositeOutputStream* getCompositeOutputStream(OutputStream* outputStream) {
    CompositeOutputStream* result = (CompositeOutputStream*) outputStream->object;

    return result;
}

/**
 * @private
 */
OutputStream* getChildOutputStream(CompositeOutputStream* compositeOutputStream, int index) {
	if (&compositeOutputStream == NULL || compositeOutputStream->maxSize == 0) {
		writeError(COMPOSITE_OUTPUT_STREAM_NOT_INITIALIZED);
		return NULL;
	}
	if (index < 0 || index >= compositeOutputStream->maxSize) {
		writeError(COMPOSITE_OUTPUT_STREAM_ILLEGAL_INDEX);
		return NULL;
	}
	OutputStream** result = (OutputStream**)compositeOutputStream->streams;
	// we don't need use sizeof because our pointer is a OutputStream* pointer, so the shift
	// is already of the structure, we just have to shift of index.
	result += index;

	return *result;
}


// Composite->OutputStream callback

void _openCompositeOutputStream(OutputStream* outputStream, int param1) {
    // don't do anything, only each leaf outputStream must be opened
}

void _closeCompositeOutputStream(OutputStream* outputStream) {
    // don't do anything, only each leaf outputStream must be closed
}

void _compositeOutputStreamWriteChar(OutputStream* outputStream, char c) {
    int i;
    CompositeOutputStream* compositeOutputStream = getCompositeOutputStream(outputStream);
    int size = compositeOutputStream->size;
    for (i = 0; i < size; i++) {
        OutputStream* childOutputStream = getChildOutputStream(compositeOutputStream, i);
        childOutputStream->writeChar(childOutputStream, c);
    }
}

void _compositeOutputStreamFlush(OutputStream* outputStream) {
    int i;
    CompositeOutputStream* compositeOutputStream = getCompositeOutputStream(outputStream);
    int size = compositeOutputStream->size;
    for (i = 0; i < size; i++) {
        OutputStream* childOutputStream = getChildOutputStream(compositeOutputStream, i);
        childOutputStream->flush(childOutputStream);
    }
}

// Composite Implementation

void addOutputStream(CompositeOutputStream* compositeOutputStream, OutputStream* childOutputStream) {
	if (compositeOutputStream == NULL || compositeOutputStream->maxSize == 0) {
		writeError(COMPOSITE_OUTPUT_STREAM_NOT_INITIALIZED);
		return;
	}

	unsigned char size = compositeOutputStream->size;
	if (size < compositeOutputStream->maxSize) {
		OutputStream** pointer = (OutputStream**)compositeOutputStream->streams;
		pointer += size;
		*pointer = childOutputStream;

		compositeOutputStream->size++;
		return;
	}
	else {
		writeError(COMPOSITE_OUTPUT_STREAM_FULL);
		return;
	}
}

int getCompositeOutputStreamChildrenCount(CompositeOutputStream* compositeOutputStream) {
    return compositeOutputStream->size;
}

void initCompositeOutputStream(CompositeOutputStream* compositeOutputStream, OutputStream*(*outputStreamArray)[], unsigned char outputStreamListSize) {
    OutputStream* outputStream = &(compositeOutputStream->outputStream);
    outputStream->openOutputStream = _openCompositeOutputStream;
    outputStream->closeOutputStream = _closeCompositeOutputStream;
    outputStream->writeChar = _compositeOutputStreamWriteChar;
    outputStream->flush = _compositeOutputStreamFlush;
    outputStream->object = (int*) compositeOutputStream;
	// TODO : Check Illegal Arguments
	compositeOutputStream->streams = outputStreamArray;
	compositeOutputStream->maxSize = outputStreamListSize;

}
