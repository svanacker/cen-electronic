#ifndef RANDOM_H
#define RANDOM_H

/**
 * Initializes the random generator.
 */
void initRandomGenerator();

/**
 * Generates a random int value between range_min and range_max (including)
 * @param range_min the min range
 * @param range max the max range
 * @return a random int value between range_min and range_max (including)
 */
int randomInRange(int range_min, int range_max);

#endif
