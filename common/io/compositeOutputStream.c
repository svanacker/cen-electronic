#include "compositeOutputStream.h"

#include "outputStream.h"

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
    return compositeOutputStream->children[index];
}


// Composite->OutputStream callbak

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
    unsigned char size = compositeOutputStream->size;
    if (size < MAX_STREAM) {
        compositeOutputStream->children[size] = childOutputStream;
        compositeOutputStream->size++;
    } else {
        appendString(getOutputStreamLogger(ERROR), "Too much composite output Stream");
    }
}

int getCompositeOutputStreamChildrenCount(CompositeOutputStream* compositeOutputStream) {
    return compositeOutputStream->size;
}

void initCompositeOutputStream(CompositeOutputStream* compositeOutputStream) {
    OutputStream* outputStream = &(compositeOutputStream->outputStream);
    outputStream->openOutputStream = _openCompositeOutputStream;
    outputStream->closeOutputStream = _closeCompositeOutputStream;
    outputStream->writeChar = _compositeOutputStreamWriteChar;
    outputStream->flush = _compositeOutputStreamFlush;
    outputStream->object = (int*) compositeOutputStream;
}
