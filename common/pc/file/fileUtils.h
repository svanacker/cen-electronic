#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>

/**
 * Get the file length in a POSIX Standard way.
 */
unsigned long readFileLength(FILE * filePointer);

#endif
