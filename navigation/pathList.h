#ifndef PATH_LIST_H
#define PATH_LIST_H

#include "../common/io/outputStream.h"

#include "path.h"
#include "location.h"
#include "locationList.h"

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
* Add a Path, with structure filled with all data.
*/
PathData* addFilledPath(PathList* pathList,
	LocationList* locationList,
	char* locationName1, char* locationName2,
	float cost,
	float controlPointDistance1, 
    float controlPointDistance2,
	float angleRadian1, 
    float angleRadian2,
	unsigned char accelerationFactor, unsigned char speedFactor,
	bool mustGoBackward);

/**
 * Get the path at index.
 */
PathData* getPath(PathList* pathList, unsigned int index);

/**
 * Returns the path corresponding to the both location.
 */
PathData* getPathOfLocations(PathList* pathList, Location* location1, Location* location2);

/**
 * Get the count of paths.
 */
unsigned int getPathCount(PathList* pathList);

// OBSTACLE MANAGEMENT

void pathListDecreaseObstacleCost(PathList* pathList);

#endif
