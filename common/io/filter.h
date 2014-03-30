#ifndef FILTER_H
#define FILTER_H

#include "../../common/commons.h"

/**
 * Filter fonction
 * @param input the char as input
 * @param output a pointer on a char
 * @return TRUE if the output must be added, false else
 */
typedef bool filterCharFunction(unsigned char input, unsigned char* output);

/**
 * A filter which transforms ascii value to decimal value.
 */
bool filterBinaryToValueChar(unsigned char c, unsigned char* output);

/**
 * A filter which removes LF and CR.
 * TO TEST
 */
bool filterRemoveCRLF(unsigned char c, unsigned char* output);

#endif

