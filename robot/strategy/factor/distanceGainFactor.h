#ifndef DISTANCE_GAIN_FACTOR_H
#define DISTANCE_GAIN_FACTOR_H

/**
 * Returns the gains factor for that distance and this number of move.
 * 
 * @param distance
 * @param numberOfMove
 * @return
 */
typedef float getDistanceGainFactorFunction(float distance, float numberOfMove);

#endif
