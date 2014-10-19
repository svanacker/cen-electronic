#include "bcdUtils.h"

char bcd2CharToDec(char bcd){
    int decimal;
    decimal = bcd >> 4;
    decimal = decimal * 10;
    decimal = decimal +(bcd & 0b00001111);
    return decimal;
}