#ifndef OUTGOING_PATH_LIST_H
#define OUTGOING_PATH_LIST_H

#include "../common/io/outputStream.h"

#include "path.h"
#include "outgoingPath.h"

/**
 * The struct defining a list of paths outgoing from a location.
 */
typedef struct {
    /** The location related to the list of outgoing Paths. */
    Location* location;
    /** An array of pointer on outgoingpaths. */
    OutgoingPathData(*outgoingPaths)[];
    /** the size of the list. */
    unsigned int size;
    /** the max size of the list. */
    unsigned int maxSize;
} OutgoingPathList;

/**
 * Initializes the outoing Path.
 * @param pathList the pathList to initialize.
 */
void initOutgoingPathList(OutgoingPathList* outgoingPathList, OutgoingPathData(*outgoingPathListArray)[], unsigned int outgoingPathListSize);

/**
 * Clear the path list.
 */
void clearOutgoingPathList(OutgoingPathList* outgoinPathList);

/**
 * Fill an outgoing path and add a path to the list.
 * @return the path from the list
 */
OutgoingPathData* addOutgoingPath(OutgoingPathList* outgoingPathList, PathData* pathData);

/**
 * Get the path at index.
 */
OutgoingPathData* getOutgoingPath(OutgoingPathList* outgoingPathList, unsigned int index);

/**
 * Get the count of outoing Paths.
 */
unsigned int getOutgoingPathCount(OutgoingPathList* outgoingPathList);

#endif
