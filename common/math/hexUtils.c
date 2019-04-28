#include "hexUtils.h"

long hex6CharToLong(unsigned char b0,
        unsigned char b1,
        unsigned char b2,
        unsigned char b3,
        unsigned char b4,
        unsigned char b5) {
    return (b0 << 20) + (b1 << 16) + (b2 << 12) + (b3 << 8) + (b4 << 4) + b5;
}

long hex4CharToLong(unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3) {
    return (b0 << 12) + (b1 << 8) + (b2 << 4) + b3;
}

int hex2CharToInt(unsigned char b0, unsigned char b1) {
    return (b0 << 4) + b1;
}




