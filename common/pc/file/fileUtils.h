#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>
#include <stdbool.h>

/**
 * Get the file length in a POSIX Standard way.
 */
unsigned long readFileLength(FILE * filePointer);

/**
* read or write some Data From File
* @param fileName the name of the file
* @param load if we load the content into the values or if we write the values
* @param fileLength the length of the values
*/
FILE* readOrWriteDataFromFile(char* fileName, bool load, char defaultValue, char* values, unsigned int valuesLength);

#endif
