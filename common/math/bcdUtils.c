#include "bcdUtils.h"

unsigned char bcd2CharToDec(unsigned char bcd) {
    int decimal;
    decimal = bcd >> 4;
    decimal = decimal * 10;
    // 0b00001111 only supported on GCC .. => We use
    decimal = decimal + (bcd & 0x0F);
    return decimal;
}
