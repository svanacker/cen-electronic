#ifndef FILTER_H
#define FILTER_H

#include "../../common/commons.h"

/**
 * Filter fonction
 * @param input the char as input
 * @param output a pointer on a char
 * @return true if the output must be added, false else
 */
typedef bool filterCharFunction(char input, char* output);

/**
 * A filter which transforms ascii value to decimal value.
 */
bool filterBinaryToValueChar(char c, char* output);

/**
 * A filter which removes LF and CR.
 * TO TEST
 */
bool filterRemoveCRLF(char c, char* output);

#endif

