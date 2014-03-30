#ifndef HCTL2032_H
#define HCTL2032_H

#include "../../common/io/outputStream.h"

/**
 * The structure to encapsulate each coders value.
 */
typedef struct {
    /** The value of the codeur */
    signed long value;
    /** The previous value of the codeur */
    signed long previousValue;
} Coder;

/**
 * The index to read the PORT X (compatible with X_Y PORT behaviour)
 */
#define X_INDEX 1
/**
 * The index to read the PORT Y.
 */
#define Y_INDEX 0

/**
 * The total number of coder which are managed.
 */
#define CODER_COUNT 2

/**
 * Init the coders.
 */
void hctl_clearCoders();

/**
 * Init the device.
 */
void initHCTL2032();

signed long hctl_getCoderValue(int coderIndex);

/**
 * Reset the coder value.
 * @param coderIndex X_INDEX or Y_INDEX
 */
void hctl_resetCoderValue(int coderIndex);

/**
 * Read the value of each coders, and store them in memory.
 */
void hctl_updateCoders();

/**
 * Returns true if any change appears on X_CODER or Y_CODER.
 */
int hctl_hasAnyCoderValueChange();

/**
 * Print the values of both coder.
 */
void hctl_printCodersValue(OutputStream* outputStream);

#endif
