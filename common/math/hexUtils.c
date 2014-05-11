#include "hexUtils.h"

float hex6CharToFloat(char b0,
        char b1,
        char b2,
        char b3,
        char b4,
        char b5) {
    return (
            ((float) b0 * 1048576.0f) +
            ((float) b1 * 65536.0f) +
            ((float) b2 * 4096.0f) +
            ((float) b3 * 256.0f) +
            ((float) b4 * 16.0f) +
            (float) b5
            );
}

long hex4CharToLong(char b0, char b1, char b2, char b3) {
    return (b0 << 12) + (b1 << 8) + (b2 << 4) + b3;
}

int hex2CharToInt(char b0, char b1) {
    return (b0 << 4) +b1;
}




