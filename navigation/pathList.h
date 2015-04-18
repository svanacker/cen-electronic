#ifndef PATH_LIST_H
#define PATH_LIST_H

#include "path.h"
#include "location.h"

/** The max limit of path count. */
#define MAX_PATH          31

/**
 * Tre struct defining a list of paths.
 */
typedef struct {
    /** An array of pointer on paths. */
    PathData(*paths)[];
    /** the size of the list. */
    unsigned int size;
    /** the max size of the list. */
    unsigned int maxSize;
} PathList;

/**
 * Initializes the path.
 * @param pathList the pathList to initialize.
 */
void initPathList(PathList* pathList, PathData(*pathListArray)[], unsigned int pathListSize);

/**
 * Clear the path list.
 */
void clearPathList(PathList* pathList);

/**
 * Fill a path and add a path to the list.
 * @return the path from the list
 */
PathData* addPath(PathList* pathList);

/**
 * Get the path at index.
 */
PathData* getPath(PathList* pathList, unsigned int index);

/**
 * Returns the path corresponding to the both location.
 */
PathData* getPathOfLocations(PathList* pathList, Location* location1, Location* location2, bool* reversed);

/**
 * Get the count of paths.
 */
unsigned int getPathCount(PathList* pathList);

/**
 * Clear the outgoing paths.
 */
void resetOutgoingPathInfo(PathList* pathList);

/**
 * Print the list of path.
 */
void printPathList(OutputStream* outputStream, char* pathListName, PathList* pathList);

#endif
