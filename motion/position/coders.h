#ifndef CODERS_H
#define CODERS_H

#include "coderType.h"

/**
 * The structure to encapsulate each coders value.
 */
typedef struct Coder {
    /** The value of the coder */
    signed long value;
    /** The previous value of the coder */
    signed long previousValue;
} Coder;

/**
 * Updates the coders values.
 */
void updateCoders(void);

/**
 * Returns the value of the coder at the specified index.
 * @param coderType the index of the coder
 * @return the coder value
 */
signed long getCoderValue(enum CoderType coderType);

#ifdef _MSC_VER
/**
 * In case of simulation on Windows, we need to set the coder Value !
 */
void setCoderValue(enum CoderType coderType, signed long value);
#endif

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
 * @param coderType the type of the coder
 * @return the error count
 */
int getCodersErrorCount(enum CoderType coderType);

/**
 * Returns the error value of the specified coder index.
 * @param index the type of coder
 * @return the error value
 */
int getCodersErrorValue(enum CoderType coderType);

/**
 * Returns the initial position of the specified coder index.
 * @param coderType the type of coder
 * @return the initial coder position
 */
signed long getCodersInitialPosition(enum CoderType coderType);

/**
 * Returns the value of the Z counter of the specified coder index.
 * @param coderType the type of coder
 * @return the value of the counter
 */
int getCodersZCount(enum CoderType coderType);

#endif
