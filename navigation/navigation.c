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
static LocationList unhandled;
static LocationList handled;
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
		if (pathContainsLocation(path, location) && !containsLocation(&handled, otherEnd)) {
			addFilledPath(&outgoingPaths, path);
		}
	}
}

int computeBestPath(LocationList* outLocationList, Location* start, Location* end) {
	clearLocationList(&unhandled);
	clearLocationList(&handled);

	// TODO : clear previous
	// TODO : clear costs

	Location* location1;

	/*

		costs.put(start, Integer.valueOf(0));
	*/
	while (!isEmptyLocationList(&unhandled)) {
		/*
		// Recherche le noeud le plus proche parmis les noeuds restants
		l1 = extractMin(unhandled, handled, costs);
		// Liste des chemins menant à ce noeud
		Collection<IPathVector> outgoingVectors = getOutgoingVectors(handled, l1);
		for (IPathVector v : outgoingVectors) {
			// Recherche parmi ces chemins du plus court
			Location l2 = v.getOtherEnd(l1);
			int dl1 = getCost(costs, l1);
			int dl2 = getCost(costs, l2);
			int d = dl1 + (int) v.getCost();
			if (d < dl2) {
				// Affectation de la distance absolue du noeud
				setCost(costs, l2, d);
				setPrevious(previous, l2, l1);
			}
		}		
		*/
	}
	/*
	// Coût
	cost.setValue(getCost(costs, end));
	// Liste des noeuds du résultat
	List<Location> path = new ArrayList<Location>();
	l1 = end;
	*/
	while ((location1 != start) && (location1 != NULL)) {
		// path.add(location1);
		// location1 = getPrevious(previous, location1);
	}
	/*
	path.add(start);
	Collections.reverse(path);
	return path;
	*/
	return 0;
}


