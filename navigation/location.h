#ifndef LOCATION_H
#define LOCATION_H

#include <stdbool.h>

#include "../common/string/cenString.h"
#include "../common/io/outputStream.h"

#define MAX_COST                               200000.0f
#define COST_IF_OBSTACLE                         5000.0f
#define COST_DECREASE_STEP                       1000.0f
#define NO_COMPUTED_COST                           -1.0f
#define MAX_DISTANCE_NEAREST_LOCATION              50.0f

struct Location;
typedef struct Location Location;

/**
 * Determine the usage of the Location.
 */
enum LocationUsageType {
    LOCATION_USAGE_TYPE_UNKNOWN = 0,
    /** The location is permanent */
    LOCATION_USAGE_TYPE_PERMANENT = 1,
    /** The location is temporary */
    LOCATION_USAGE_TYPE_TEMPORARY = 2,
    /** The location was temporary, but we could now reuse it (kind of garbage collector behaviour */
    LOCATION_USAGE_TYPE_TO_BE_REUSE = 3
};

enum LocationAdjustType {
    /** We don't adjust at this point. */
    LOCATION_ADJUST_NONE = 0,
    /** We could (but not mandatory.) adjust in X */
    LOCATION_ADJUST_X = 1,
    /** We could (but not mandatory.) adjust in Y */
    LOCATION_ADJUST_Y = 2
};

/**
 * Encapsulates the location.
 */
struct Location {
    /** Usage type (for memory management) */
    enum LocationUsageType usageType;
    /** The name (fixed to be able to interact in console with them). */
    FixedCharArray name;
    /** The label of the point */
    char* label;
    /** The coordinates in x. */
    float x;
    /** The coordinates in y. */
    float y;
    /** If we must adjust. */
    enum LocationAdjustType adjustType;
    /** The value (X, Y) for which we adjust. For angle, we assume that the angle is a multiple of quadrant (0, 45, 90 ...) */
    float adjustValue;
    /** Temporary Computer information needed by path finding algorithm. */
    float computedCost;
    /** Temporary Computer information needed by path finding algorithm. */
    bool computedHandled;
    /** Result Computer information with the next location to follow the path. */
    Location* computedNextLocation;
    /** Result Computer information with the previous location to follow the path. */
    Location* computedPreviousLocation;
};

/**
 * Equals function on Location. The equals is based on the name of the location !
 */
bool locationEquals(Location* location1, Location* location2);

// UTILS METHODS

/**
 * "Fly" distance between the 2 locations;
 */
float distanceBetweenLocations(Location* location1, Location* location2);

#endif
