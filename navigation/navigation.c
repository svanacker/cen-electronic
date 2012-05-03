#include <stdlib.h>

#include "navigation.h"
#include "location.h"
#include "locationList.h"
#include "path.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

#include "../common/log/logger.h"
#include "../common/log/logLevel.h"

/** All locations. */
static LocationList locations;

/** All paths. */
static PathList paths;

// private members (avoid using Stack to avoid runtime problems)
static LocationList unhandledLocationList;
static LocationList handledLocationList;
// TODO : Map<Location, Location> previous
static PathList outgoingPaths;
// static Location nearestLocation;

void addNavigationLocation(Location* location, char* name, int x, int y) {
	addLocation(&locations, location, name, x, y);
}

void addNavigationPath(  Path* path, 
						 Location* location1,
						 Location* location2, 
						 int cost,
						 int controlPointDistance1,
						 int controlPointDistance2,
						 int angle1,
						 int angle2,
						 int speedFactor) {
	addPath(&paths, path, location1, location2, cost, controlPointDistance1, controlPointDistance2, angle1, angle2, speedFactor); 
}

void updateOutgoingPaths(Location* location) {
	clearPathList(&outgoingPaths);
	int i;
	int pathSize = getPathCount(&paths);
	for (i = 0; i < pathSize; i++) {
		Path* path = getPath(&paths, i);
		Location* otherEnd = getOtherEnd(path, location);
		if (pathContainsLocation(path, location) && !containsLocation(&handledLocationList, otherEnd)) {
			addFilledPath(&outgoingPaths, path);
		}
	}
}

void clearLocationTmpCosts(LocationList* locationList) {
	int i;
	unsigned char size = locationList->size;
	for (i = 0; i < size; i++) {
		Location* location = locationList->locations[i];
		// We can have hole because of "remove"
		if (location == NULL) {
			continue;
		}
		location->tmpCost = NO_COMPUTED_COST;
	}
}

/** 
 * Returns the cost associated to location.
 */
unsigned int getCost(Location* location) {
	if (location->tmpCost == NO_COMPUTED_COST) {
		return MAX_COST;
	}
	return location->tmpCost;
}

/**
 * Change the cost associated to the location.
 */
void setCost(Location* location, int cost) {
	location->tmpCost = cost;
}

/**
 * @private
 * Search the nearest node in terms of cost
 */
Location* extractMinCostLocation() {
	OutputStream* outputStream = getOutputStreamLogger(DEBUG);
	appendString(outputStream, "extractMinCostLocation\n");
	// Search the nearest node in terms of cost
	Location* result = NULL;
	int minCost = MAX_COST;
	int size = unhandledLocationList.size;
	int i;
	for (i = 0; i < size; i++) {
		Location* location = unhandledLocationList.locations[i];
		// We can have hole because of remove operation
		if (location == NULL) {
			continue;
		}
		printLocation(outputStream, location);

		// get the cost (
		int cost = getCost(location);
		if (cost <= minCost) {
			minCost = cost;
			result = location;
			appendStringAndDec(outputStream, "result=", cost);
			println(outputStream);
		}
	}
	removeLocation(&unhandledLocationList, result);
	// TODO : Manage equals because it is a set !!!
	addFilledLocation(&handledLocationList, result);
	return result;
}

int computeBestPath(LocationList* outLocationList, Location* start, Location* end) {
	/*
	Set<Location> locations = new HashSet<Location>();
	for (IPathVector v : map.getPathVectors()) {
		locations.add(v.getStart());
		locations.add(v.getEnd());
	}
	*/

	int result = 0;
	clearLocationList(outLocationList);
	clearLocationList(&unhandledLocationList);
	clearLocationList(&handledLocationList);

	addLocationList(&unhandledLocationList, &locations);

	// TODO : clear previous
	// TODO : clear costs
	// clearLocationTmpCosts();

	Location* location1;

	start->tmpCost = 0;
	while (!isEmptyLocationList(&unhandledLocationList)) {
		// search the nearest node of the nodeList
		location1 = extractMinCostLocation();

		// List of path going to the node (location)
		updateOutgoingPaths(location1);

		int i;
		int size = outgoingPaths.size;
		for (i = 0; i < size; i++) {
			Path* path = getPath(&outgoingPaths, i);

			Location* location2 = getOtherEnd(path, location1);
			int costLocation1 = getCost(location1);
			int costLocation2 = getCost(location2);

			int cost = costLocation1 + path->cost;
			if (cost < costLocation2) {
				// Affectation de la distance absolue du noeud
				setCost(location2, cost);
				// setPrevious(previous, location2, location1);
			}
		}		
	}
	result = getCost(end);
	location1 = end;
	
	/*
	while ((location1 != start) && (location1 != NULL)) {
		addFilledLocation(outLocationList, location1);
		// location1 = getPrevious(previous, location1);
	}
	*/
	// addFilledLocation(outLocationList, start);
	// Collections.reverse(path);

	return result;
}

void printNavigationContext(OutputStream* outputStream) {
	printLocationList(outputStream, "locations:", &locations);
	printPathList(outputStream, "paths:", &paths);

	printLocationList(outputStream, "handledLocationList:", &handledLocationList);
}
