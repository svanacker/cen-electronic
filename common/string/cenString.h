#ifndef CEN_STRING_H
#define CEN_STRING_H

#include <stdbool.h>

// Char / Strings typedef
#define FIXED_CHAR_ARRAY_LENGTH         4
// We reserve the last char as '\0' to be sure that we will not continue, if we use "string" routines
typedef unsigned char FixedCharArray [FIXED_CHAR_ARRAY_LENGTH];

bool fixedCharArrayEquals(FixedCharArray* fixedCharArray1, FixedCharArray* fixedCharArray2);

/**
 * Copy a fixed char array from a source to a target.
 * @param source the source fixed char array
 * @param target the target fixed char array
 */
void copyFixedCharArray(FixedCharArray* source, FixedCharArray* target);

/**
 * Clear the content of the fixedCharArray by filling the content to '\0'.
 * @param fixedCharArray the char array to clear
 */
void clearFixedCharArray(FixedCharArray* fixedCharArray);

/**
 * Fill a fixedCharArray from a string.
 * @param s the string from which the content must be copied
 * @param fixedCharArray the fixed Array Char which must be filled by the content of the string
 * @return true if the all content of the string was filled (because the size is < length(fixedCharArray)), else if all other cases.
 */
bool stringToFixedCharArray(const char* s, FixedCharArray* fixedCharArray);

/**
 * Returns if both strings are equal or not.
 * @param s1 the first string to compare
 * @param s2 the second string to compare
 * @return true if both strings are equal, false else
 */
bool stringEquals(const char* s1, const char* s2);

#endif
