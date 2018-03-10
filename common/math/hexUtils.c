#include "hexUtils.h"

long hex6CharToLong(char b0,
        char b1,
        char b2,
        char b3,
        char b4,
        char b5) {
    return (b0 << 20) + (b1 << 16) + (b2 << 12) + (b3 << 8) + (b4 << 4) + b5;
}

long hex4CharToLong(char b0, char b1, char b2, char b3) {
    return (b0 << 12) + (b1 << 8) + (b2 << 4) + b3;
}

int hex2CharToInt(char b0, char b1) {
    return (b0 << 4) + b1;
}




