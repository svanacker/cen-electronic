#include "filter.h"

#include "../../common/commons.h"

// TRANFORMATION BINARY -> ASCII

BOOL filterBinaryToValueChar(unsigned char c, unsigned char* output) {
    // c in ['0'..'9']
    if ((c >= 48) && (c <= 57)) {
        // translate value in [0..9]
        *output = c - 48;
        return TRUE;
    }// c in ['A'..'F']
    else if ((c >= 65) && (c <= 70)) {
        // Transform it to value between 10 and 15
        *output = c - 55;
        return TRUE;
    }        // c in ['G'..'Z']
    else if ((c >= 71) && (c <= 90)) {
        // append the character instruction to the buffer
        *output = c;
        return TRUE;
    }// c in ['a'..'z']
    else if ((c >= 97) && (c <= 122)) {
        *output = c;
        return TRUE;
    }        // Others special Chars

        // c in ['!'..'/']
    else if ((c >= 33) && (c <= 47)) {
        *output = c;
        return TRUE;
    }// c in [':'..'@']
    else if ((c >= 58) && (c <= 64)) {
        *output = c;
        return TRUE;
    }

    return FALSE;
}

BOOL filterRemoveCRLF(unsigned char c, unsigned char* output) {
    if (c == CR || c == LF) {
        return FALSE;
    }
    *output = c;
    return TRUE;
}
