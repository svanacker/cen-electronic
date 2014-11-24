#include "filter.h"

#include <stdbool.h>

#include "../../common/commons.h"

// TRANFORMATION BINARY -> ASCII

bool filterBinaryToValueChar(char c, char* output) {
    // Order by most cases !
    // c in ['0'..'9']
    if ((c >= 48) && (c <= 57)) {
        // translate value in [0..9]
        *output = c - 48;
        return true;
    }
    // c in ['A'..'F']
    else if ((c >= 65) && (c <= 70)) {
        // Transform it to value between 10 and 15
        *output = c - 55;
        return true;
    }
    // c in ['G'..'Z']
    else if ((c >= 71) && (c <= 90)) {
        // append the character instruction to the buffer
        *output = c;
        return true;
    }
    // c in ['a'..'z']
    else if ((c >= 97) && (c <= 122)) {
        *output = c;
        return true;
    }
    // c in ['!'..'/']
    else if ((c >= 33) && (c <= 47)) {
        *output = c;
        return true;
    }
    // c in [':'..'@']
    else if ((c >= 58) && (c <= 64)) {
        *output = c;
        return true;
    }
    // c in ['{'..'}']
    else if ((c >= 123) && (c <= 125)) {
        *output = c;
        return true;
    }
    *output = c;
    return false;
}

bool filterRemoveCRLF(char c, char* output) {
    *output = c;
    if (c == CR || c == LF) {
        return false;
    }
    return true;
}
