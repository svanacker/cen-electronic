#ifndef PATH_LIST_H
#define PATH_LIST_H

#include "path.h"
#include "location.h"

/** The max limit of path count. */
#define MAX_PATH 	 	40

/**
 * Tre struct defining a list of locations.
 */
typedef struct {
    /** An array of pointer on paths. */
    PathDataFunction* paths[MAX_PATH];
    /** the size of the list. */
    unsigned char size;
} PathList;


/**
 * Clear the path list.
 */
void clearPathList(PathList* pathList);

/**
 * Fill a path and add a path to the list.
 * @param path the path to add to the list
 */
void addPath(PathList* pathList,
			 PathDataFunction* pathDataFunction);

/**
 * Get the path at index.
 */
PathDataFunction* getPath(PathList* pathList, int index);

/**
 * Returns the path corresponding to the both location.
 */
PathDataFunction* getPathOfLocations(PathList* pathList, Location* location1, Location* location2, BOOL* reversed);

/**
 * Get the count of paths.
 */
int getPathCount(PathList* pathList);

/**
 * Clear the outgoing paths.
 */
void resetOutgoingPathInfo(PathList* pathList);

/**
 * Print the list of path.
 */
void printPathList(OutputStream* outputStream, char* pathListName, PathList* pathList);

#endif
