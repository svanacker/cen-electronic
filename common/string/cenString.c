#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "cenString.h"

bool stringEquals(const char* s1, const char* s2) {
    int comparison = strcmp(s1, s2);
    return (comparison == 0);
}

// TODO : Add Unit Test
bool fixedCharArrayEquals(FixedCharArray* fixedCharArray1, FixedCharArray* fixedCharArray2) {
    if (fixedCharArray1 == NULL || fixedCharArray2 == NULL) {
        // TODO : Throw an error
        return false;
    }
    int i;
    char* cPointer1 = (char*)fixedCharArray1;
    char* cPointer2 = (char*)fixedCharArray2;

    for (i = 0; i < FIXED_CHAR_ARRAY_LENGTH; i++) {
        char c1 = *cPointer1;
        char c2 = *cPointer2;
        cPointer1++;
        cPointer2++;

        if (c1 != c2) {
            return false;
        }
    }
    return true;
}

void clearFixedCharArray(FixedCharArray* fixedCharArray) {
    int i;
    char* cPointer = (char*)fixedCharArray;
    for (i = 0; i < FIXED_CHAR_ARRAY_LENGTH; i++) {
        *cPointer = '\0';
        cPointer++;
    }
}

void copyFixedCharArray(FixedCharArray* source, FixedCharArray* target) {
    if (source == NULL || target == NULL) {
        // TODO : Throw an error
        return;
    }
    int i;
    char* sourcePointer = (char*)source;
    char* targetPointer = (char*)target;
    for (i = 0; i < FIXED_CHAR_ARRAY_LENGTH; i++) {
        *targetPointer = *sourcePointer;
        sourcePointer++;
        targetPointer++;
    }
}

bool stringToFixedCharArray(const char* s, FixedCharArray* fixedCharArray) {
    if (s == NULL || fixedCharArray == NULL) {
        // TODO : Throw an error
        return false;
    }
    int index = 0;
    char* pointer = (char*)fixedCharArray;
    while (*s != '\0') {
        *pointer = *s++;
        pointer++;
        index++;
        if (index >= FIXED_CHAR_ARRAY_LENGTH) {
            break;
        }
    }
    while (index < FIXED_CHAR_ARRAY_LENGTH) {
        *pointer = '\0';
        pointer++;
        index++;
    }
    return strlen(s) > FIXED_CHAR_ARRAY_LENGTH;
}