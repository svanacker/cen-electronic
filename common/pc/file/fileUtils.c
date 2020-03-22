#include "fileUtils.h"

#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

unsigned long readFileLength(FILE * filePointer) {
    fseek(filePointer, 0L, SEEK_END);
    unsigned result = ftell(filePointer);

    fseek(filePointer, 0L, SEEK_SET);

    return result;
}

FILE* readOrWriteDataFromFile(char* fileName, bool load, char defaultValue, char* values, unsigned int valuesLength) {
    FILE* result = fopen(fileName, "rb+");
    // if file does not exist, create it
    if (result == NULL) {
        int i;
        char* initValues = values;
        for (i = 0; i < valuesLength; i++) {
            *initValues = defaultValue;
            initValues++;
        }

        result = fopen(fileName, "wb");
        // Write the default values
        fwrite(values, 1, valuesLength, result);
        fclose(result);
    }
    else {
        // In all cases
        if (load) {
            fread(values, 1, valuesLength, result);
            fclose(result);
        }
        else {
            // Fill data
            fwrite(values, 1, valuesLength, result);
            fclose(result);
        }
    }
    return result;
 }