#ifndef OUTGOING_PATH_H
#define OUTGOING_PATH_H

#include <stdbool.h>

#include "path.h"

/**
 * Contains a reference to a path and the outgoing information.
 */
typedef struct OutgoingPathData {
    /** the PathData */
    PathData* pathData;
} OutgoingPathData;

#endif
