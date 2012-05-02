#ifndef PATH_LIST_H
#define PATH_LIST_H

#include "path.h"
#include "location.h"

/** The max limit of path count. */
#define MAX_PATH 	 	20

/**
 * Tre struct defining a list of locations.
 */
typedef struct {
    /** An array of pointer on paths. */
    Path* paths[MAX_PATH];
    /** the size of the list. */
    unsigned char size;
} PathList;


/**
 * Add a path to the list.
 * @param path the path to add to the list
 */
void addPath(PathList* pathList,
			 Path* path, 
			 Location* location1,
			 Location* location2, 
			 int controlPointDistance1,
			 int controlPointDistance2,
			 int angle1,
			 int angle2,
			 int cost,
			 int speedFactor);

/**
 * Get the path at index.
 */
Path* getPath(PathList* pathList, int index);

/**
 * Get the count of paths.
 */
int getPathCount(PathList* pathList);

#endif
