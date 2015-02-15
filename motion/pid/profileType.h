#ifndef PROFILE_TYPE_H
#define PROFILE_TYPE_H

typedef unsigned char ProfileType;

/** Acceleration phase / constant speed / Deceleration phase. */
#define PROFILE_TYPE_TRAPEZE 0

/** Type of trajectory in which we do not reach the max speed (=> acceleration phase, deceleration phase). */
#define PROFILE_TYPE_TRIANGLE 1

#endif
