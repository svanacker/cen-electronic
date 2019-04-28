#ifndef COMPOSITE_OUTPUT_STREAM_H
#define COMPOSITE_OUTPUT_STREAM_H

#include "outputStream.h"

/**
* Structure defining a composite of streams.
*/
typedef struct CompositeOutputStream {
    // The outputStream exposed as an interface
    OutputStream outputStream;
    /** An array of pointer on outputStream pointer. */
    OutputStream*(*streams)[];
    /** the size of the list. */
    unsigned int size;
    /** the max size of the list. */
    unsigned int maxSize;
} CompositeOutputStream;

/**
* Add a stream to the composite.
* @param compositeOutputStream the composite in which we add a sub outputStream
* @param childOutputStream the outputStream to add
*/
void addOutputStream(CompositeOutputStream* compositeOutputStream, OutputStream* childOutputStream);

/**
* Returns the children.
* @param compositeOutputStream the stream containing child.
* @return the number of outputStream children
*/
int getCompositeOutputStreamChildrenCount(CompositeOutputStream* compositeOutputStream);

/**
* Init a compositeOutputStream, and branch the outputStream exposed to use the streams children.
* @param compositeOutputStream the composite stream to initialize

*/
void initCompositeOutputStream(CompositeOutputStream* compositeOutputStream, OutputStream*(*outputStreamListArray)[], unsigned int outputStreamListSize);

#endif
