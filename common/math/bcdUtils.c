#include "bcdUtils.h"

unsigned char bcd2CharToDec(unsigned char bcd) {
    int decimal;
    decimal = bcd >> 4;
    decimal = decimal * 10;
    // 0b00001111 only supported on GCC .. => We use hexa
    decimal = decimal + (bcd & 0x0F);
    return decimal;
}

unsigned int bcd4CharToDec(unsigned int bcd) {
    int i;
    int decimal;
    decimal = bcd >> 12;    
    for  (i = 0; i < 3; i++){
        decimal = decimal * 10;
        bcd = bcd << 4 & 0xFFF0;
        decimal = decimal + ((bcd & 0xF000) >> 12);       
    }
    return decimal;
}