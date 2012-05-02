#include <stdlib.h>

#include "navigation.h"
#include "location.h"
#include "locationList.h"
#include "path.h"

/** All locations. */
static LocationList locations;

/** All paths. */
static PathList paths;

// private members (avoid using Stack to avoid runtime problems)
static LocationList unhandledLocationList;
static LocationList handledLocationList;
// TODO : Map<Location, Location> previous
// TODO : Map<Location, Integer> costs
static PathList outgoingPaths;
static Location nearestLocation;

void addNavigationLocation(Location* location, char* name, int x, int y) {
	addLocation(&locations, location, name, x, y);
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

/** 
 *
 */
unsigned int getCost(Location* location) {
	if (location == NULL) {
		
	}
}

/**
 * @private
 * Search the nearest node in terms of cost
 */
Location* extractMin() {
	// Search the nearest node in terms of cost
	Location* result = NULL;
	int minCost = MAX_COST;
	int i;
	int size = unhandledLocationList.size;
	for (i = 0; i < size; i++) {
		Location* unhandledLocation = unhandledLocationList.locations[i];
		// We can have hole because of remove operation
		if (unhandledLocation == NULL) {
			continue;
		}
		// get the cost (
		int cost = getCost(unhandledLocation);
		if (cost <= minCost) {
			minCost = cost;
			result = unhandledLocation;
		}
	}
	removeLocation(&unhandledLocationList, result);
	// TODO : Manage equals because it is a set !!!
	addFilledLocation(&handledLocationList, result);
	return result;
}

int computeBestPath(LocationList* outLocationList, Location* start, Location* end) {
	clearLocationList(outLocationList);
	clearLocationList(&unhandledLocationList);
	clearLocationList(&handledLocationList);

	// TODO : clear previous
	// TODO : clear costs

	Location* location1;

	start->tmpCost = 0;
	while (!isEmptyLocationList(&unhandledLocationList)) {
		/*
		// Recherche le noeud le plus proche parmis les noeuds restants
		l1 = extractMin(unhandled, handled, costs);
		*/
		// List of path going to the node (location)
		updateOutgoingPaths(location1);
		int i;
		int size = outgoingPaths.size;
		for (i = 0; i < size; i++) {
			Path* path = getPath(&outgoingPaths, i);
			// Recherche parmi ces chemins du plus court
			Location* location2 = getOtherEnd(path, location1);
			/*
			int costLocation1 = getCost(costs, location1);
			int costLocation2 = getCost(costs, location2);
			int cost = costLocation1 + (int) v.getCost();
			if (cost < costLocation2) {
				// Affectation de la distance absolue du noeud
				setCost(costs, location2, cost);
				setPrevious(previous, location2, location1);
			}
			*/
		}		
	}
	/*
	// Coût
	cost.setValue(getCost(costs, end));
	// Liste des noeuds du résultat
	List<Location> path = new ArrayList<Location>();
	l1 = end;
	*/
	while ((location1 != start) && (location1 != NULL)) {
		addFilledLocation(outLocationList, location1);
		// location1 = getPrevious(previous, location1);
	}
	addFilledLocation(outLocationList, start);
	// Collections.reverse(path);

	// TODO : return cost
	return 0;
}


