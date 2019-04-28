#ifndef HEX_UTILS_H
#define HEX_UTILS_H

/**
 * Transform the hexadecimal value (6 bytes length) and return it.
 * the hexadecimal value must be in Up case.
 * Ex : 2001AF
 * @param b0 value between 0 and 15
 * @param b1 value between 0 and 15
 * @param b2 value between 0 and 15
 * @param b3 value between 0 and 15
 * @param b4 value between 0 and 15
 * @param b5 value between 0 and 15
 * @return value value between 0 and 2^32 - 1
 */
long hex6CharToLong(unsigned char b0,
        unsigned char b1,
        unsigned char b2,
        unsigned char b3,
        unsigned char b4,
        unsigned char b5);

/**
 * Transform the hexadecimal value (4 bytes length) and return it.
 * the hexadecimal value must be in Up case.
 * Ex : 01AF
 * @param b0 value between 0 and 15
 * @param b1 value between 0 and 15
 * @param b2 value between 0 and 15
 * @param b3 value between 0 and 15
 * @return value value between 0 and 65535
 */
long hex4CharToLong(unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3);

/**
 * Transforms the hexadecimal value (2 bytes length) into a int value.
 * the hexadecimal value must be in Up case.
 * Ex : 0A
 * @param b0 value between 0 and 15
 * @param b1 value between 0 and 15
 * @return the hexadecimal value (value between 0 and 255)
 */
int hex2CharToInt(unsigned char b0, unsigned char b1);

#endif
