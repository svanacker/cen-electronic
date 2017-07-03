#ifndef BCD_UTILS_H
#define BCD_UTILS_H

/**
 * Transform the BCD value.
 * Ex 0x28-> 28 decimal
 * @param bcd the bcd number to convert
 * @result decimal the decimal number result
 */
unsigned char bcd2CharToDec(unsigned char bcd);

/**
 * Transform the BCD value.
 * Ex 0x28-> 28 decimal
 * @param bcd the bcd number to convert
 * @result decimal the decimal number result
 */
unsigned int bcd4CharToDec(unsigned int bcd);


#endif    

