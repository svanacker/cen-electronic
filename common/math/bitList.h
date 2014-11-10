#ifndef BIT_LIST_H
#define BIT_LIST_H

#include "../../common/commons.h"
#include "../../common/io/outputStream.h"

#define BITS_COUNT_IN_UNSIGNED_INT            16

/**
 * Define a structure which stores bool value as bit of 16 bits values.
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
 * @param bitList the pointer on object (POO simulation)
 * @param array the array of int used to store bit
 * @param arrayLength the length of the int array (and not the size of bool list)
 */
void initBitList(BitList* bitList, unsigned int (*array)[], unsigned char arrayLength);

/**
 * Clear the bit list to false for every values.
 * @param bitList the pointer on object (POO simulation)
 * @param initValue the initial value for clear bits
 */
void clearBitList(BitList* bitList, bool initValue);

/**
 * Set the bit at the right index to the list.
 * @param bitList the pointer on object (POO simulation)
 * @param index the index of bit that we use
 * @param value the value of the bool at the index
 * @throw error if index is too bug for the array of int bits which was provider.
 */
void setBit(BitList* bitList, unsigned char index, bool value);

/**
 * Returns the bit at the right index to the list. 
 * @param bitList the pointer on object (POO simulation)
 * @param index the index of bit that we want to get
 * @throw error if index is too bug for the array of int bits which was provider.
 */
bool getBit(BitList* bitList, unsigned char index);

// DEBUG

/**
 * Print the list of bit to an outputStream (as 0/1).
 * @param outputStream the outputStream where we writes the information
 * @param bitList the pointer on object (POO simulation)
 */
void printBitList(OutputStream* outputStream, BitList* bitList);

#endif
