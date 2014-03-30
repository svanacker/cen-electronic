#include "hexUtils.h"

float hex6CharToFloat(unsigned char b0,
        unsigned char b1,
        unsigned char b2,
        unsigned char b3,
        unsigned char b4,
        unsigned char b5) {
    return (
            ((float) b0 * 1048576.0f) +
            ((float) b1 * 65536.0f) +
            ((float) b2 * 4096.0f) +
            ((float) b3 * 256.0f) +
            ((float) b4 * 16.0f) +
            (float) b5
            );
}

long hex4CharToLong(unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3) {
    return (b0 << 12) + (b1 << 8) + (b2 << 4) + b3;
}

int hex2CharToInt(unsigned char b0, unsigned char b1) {
    return (b0 << 4) +b1;
}




