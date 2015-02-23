#ifndef CODERS_H
#define CODERS_H

#include "coderType.h"

/** The index of timer used. */
#define CODER_TIMER_INDEX 0

/**
 * Updates the coders values.
 */
void updateCoders(void);

/**
 * Returns the value of the coder at the specified index.
 * @param index the index of the coder
 * @return the coder value
 */
signed long getCoderValue(enum CoderType coderType);

/**
 * Clears the coders values.
 */
void clearCoders(void);

/**
 * Initializes the coders.
 */
void initCoders(void);

/**
 * Checks the coders errors.
 */
void checkCoders(void);

/**
 * Returns the error count of the specified coder index.
 * @param index the index of the coder
 * @return the error count
 */
int getCodersErrorCount(int index);

/**
 * Returns the error value of the specified coder index.
 * @param index the index of the coder
 * @return the error value
 */
int getCodersErrorValue(int index);

/**
 * Returns the initial position of the specified coder index.
 * @param index the index of the coder
 * @return the initial coder position
 */
signed long getCodersInitialPosition(int index);

/**
 * Returns the value of the Z counter of the specified coder index.
 * @param index the index of the coder
 * @return the value of the counter
 */
int getCodersZCount(int index);

#endif
