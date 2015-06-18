#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "cenString.h"

bool stringEquals(char* s1, char* s2) {
    int comparison = strcmp(s1, s2);
    return (comparison == 0);
}

void clearFixedCharArray(FixedCharArray* fixedCharArray) {
    int i;
    for (i = 0; i < FIXED_CHAR_ARRAY_LENGTH; i++) {
        *fixedCharArray[i] = '\0';
    }
}

void copyFixedCharArray(FixedCharArray* source, FixedCharArray* target) {
    if (source == NULL || target == NULL) {
        // TODO : Throw an error
        return;
    }
    int i;
    for (i = 0; i < FIXED_CHAR_ARRAY_LENGTH; i++) {
        *target[i] = *source[i];
    }
}

void stringToFixedCharArray(char* s, FixedCharArray* fixedCharArray) {
    if (s == NULL || fixedCharArray == NULL) {
        // TODO : Throw an error
        return;
    }
    int index = 0;
    while (*s != '\0') {
        *fixedCharArray[index] = *s++;
        index++;
        if (index >= FIXED_CHAR_ARRAY_LENGTH) {
            break;
        }
    }
    while (index < FIXED_CHAR_ARRAY_LENGTH) {
        *fixedCharArray[index] = '\0';
        index++;
    }
}