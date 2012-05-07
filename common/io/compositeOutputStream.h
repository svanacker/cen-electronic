#ifndef COMPOSITE_OUTPUT_STREAM_H
#define COMPOSITE_OUTPUT_STREAM_H

#include "outputStream.h"

#define MAX_STREAM 2

/**
* Structure defining a composite of streams.
*/
typedef struct CompositeOutputStream {
	/** The array of sub-streams. */
	OutputStream* children[MAX_STREAM];
	/** The real size of the outputStream. */
	unsigned char size;
	// The outputStream exposed as an interface
	OutputStream outputStream;
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
*/
int getCompositeOutputStreamChildrenCount(CompositeOutputStream* compositeOutputStream);

/**
* Init a compositeOutputStream, and branch the outputStream exposed to use the streams children.
* @param compositeOutputStream the composite stream to initialize
*/
void initCompositeOutputStream(CompositeOutputStream* compositeOutputStream);

#endif
