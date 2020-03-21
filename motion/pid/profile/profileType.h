#ifndef PROFILE_TYPE_H
#define PROFILE_TYPE_H

#include "../../../common/io/outputStream.h"

/**
 * The profile of the motion. If we reach the speed max, it will be a Trapeze, if we don't have time to reach speed max, it will be a triangle
 */
enum ProfileType {
    /** Undefined profile */
    PROFILE_TYPE_UNDEFINED = 0,

    /** Acceleration phase / constant speed / Deceleration phase. */
    PROFILE_TYPE_TRAPEZE = 1,

    /** Type of trajectory in which we do not reach the max speed (=> acceleration phase, deceleration phase). */
    PROFILE_TYPE_TRIANGLE = 2
};

/**
 * Append in the stream a string representation of the enum ProfileType.
 */
unsigned int appendProfileTypeAsString(OutputStream* outputStream, enum ProfileType profileType);

/**
 * Append a column value with the profile type.
 */
unsigned int addMotionProfileTypeTableData(OutputStream* outputStream, enum ProfileType profileType, int columnSize);

#endif
