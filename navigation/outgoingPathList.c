#include <stdlib.h>

#include "outgoingPathList.h"
#include "path.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

#include "../common/error/error.h"

void initOutgoingPathList(OutgoingPathList* outgoingPathList, OutgoingPathData(*outgoingPathListArray)[], unsigned int pathListSize) {
    if (outgoingPathList == NULL) {
        writeError(OUTGOING_PATH_LIST_NULL);
        return;
    }
    outgoingPathList->outgoingPaths = outgoingPathListArray;
    outgoingPathList->maxSize = pathListSize;
}

void clearOutgoingPathList(OutgoingPathList* outgoingPathList) {
    outgoingPathList->size = 0;
}

OutgoingPathData* addOutgoingPath(OutgoingPathList* outgoingPathList, PathData* pathData) {
    if (outgoingPathList == NULL || outgoingPathList->maxSize == 0) {
        writeError(OUTGOING_PATH_LIST_NOT_INITIALIZED);
        return NULL;
    }

    unsigned int size = outgoingPathList->size;
    if (size < outgoingPathList->maxSize) {
        OutgoingPathData* outgoingPathData = getOutgoingPath(outgoingPathList, size);
        outgoingPathData->pathData = pathData;
        outgoingPathList->size++;
        return outgoingPathData;
    }
    else {
        writeError(TOO_MUCH_PATHS);
        return NULL;
    }
}

OutgoingPathData* getOutgoingPath(OutgoingPathList* outgoingPathList, unsigned int index) {
    if (outgoingPathList == NULL || outgoingPathList->maxSize == 0) {
        writeError(OUTGOING_PATH_LIST_NOT_INITIALIZED);
        return NULL;
    }
    if (index < 0 || index >= outgoingPathList->maxSize) {
        writeError(OUTGOING_PATH_LIST_INDEX_OUT_OF_BOUNDS);
        return NULL;
    }
    OutgoingPathData* result = (OutgoingPathData*) outgoingPathList->outgoingPaths;
    // we don't need use sizeof because our pointer is a OutgoingPathData* pointer, so the shift
    // is already of the structure, we just have to shift of index.
    result += index;

    return result;
}

unsigned int getOutgoingPathCount(OutgoingPathList* outgoingPathList) {
    return outgoingPathList->size;
}
