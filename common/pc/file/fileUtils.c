#include "fileUtils.h"

#include <stdio.h>

unsigned long readFileLength(FILE * filePointer) {
    fseek(filePointer, 0L, SEEK_END);
    unsigned result = ftell(filePointer);

    fseek(filePointer, 0L, SEEK_SET);

    return result;
}
