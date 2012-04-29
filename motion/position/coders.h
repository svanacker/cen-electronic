#ifndef CODERS_H
#define CODERS_H

/** The number of coders which are managed. */
#define MAX_CODERS 2

#define CODER_LEFT 0
#define CODER_RIGHT 1

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
signed long getCoderValue(int index);

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
