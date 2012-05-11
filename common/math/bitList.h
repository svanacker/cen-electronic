#ifndef BIT_LIST_H
#define BIT_LIST_H

#include "../../common/commons.h"

#include "../../common/io/outputStream.h"

#define BITS_COUNT_IN_UNSIGNED_INT			16

/**
 * Define a structure which stores BOOL value as bit of 16 bits values.
 * For a size of x bits, we need x / BITS_COUNT_IN_UNSIGNED_INT array value
 */
typedef struct {
    /** A pointer on an array of unsigned int. */
    unsigned int (*array)[];
	/** The size of the list (number of bits). */
	unsigned int size;
	/** The max length of the array = RoundUp(number of bits / BITS_COUNT_IN_UNSIGNED_INT). */
	unsigned char arrayLength;
} BitList;

/**
 * Initialize the bit List with the underlying int array.
 * @param arrayLength the length of the int array (and not the size of BOOL list)
 */
void initBitList(BitList* bitList, unsigned int (*array)[], unsigned char arrayLength);

/**
 * Clear the bit list to FALSE for every values.
 */
void clearBitList(BitList* bitList);

/**
 * Set the bit at the right index to the list.
 * @throw error if index is too bug for the array of int bits which was provider.
 */
void setBit(BitList* bitList, unsigned char index, BOOL value);

/**
 * Returns the bit at the right index to the list. 
 * @throw error if index is too bug for the array of int bits which was provider.
 */
BOOL getBit(BitList* bitList, unsigned char index);

// DEBUG

/**
 * Print the list of bit to an outputStream (as 0/1).
 */
void printBitList(OutputStream* outputStream, BitList* bitList);

#endif
