#ifndef ST24C16_H
#define	ST24C16_H

#include "../../common/io/buffer.h"

/**
* write one data in the Eeprom at the index address
* @param index          The index for select the address
* @param value          the value to write
*/
void writeEepromInt(unsigned int index, signed int value);

/**
* read the value in the Eeprom at the index address
* @param index          The index for select the address
* @return data          the data read from the eeprom
*/
unsigned int readEepromInt (unsigned int index);

/**
* calculate the chip address to select
* @param    index               the index to calculate the chip Address
* @return   blocAddress         the chip address to select
*/
unsigned int setBlocAddress (unsigned int index);

/**
* calculate the address in the chip to select
* @param index              the index for calculate the address
* @return address           the address result
*/
unsigned int setAddress (unsigned int index);

/**
* Read values from the EEPROM device.
* Slave will return all values and store them in the buffer
* @param index          the random address to read
* @param length         the number of data to read
* @param Buffer* buffer the buffer
*/
void readEepromBloc(unsigned int index, char length, Buffer* buffer);

/** BY JEROME
 * Write  the values from the buffer in the EEPROM chip
 * @param index                         the random address to write
 * @param length                        the number of data to write
 * @param Buffer* buffer                the buffer
 */
void writeEepromBloc (unsigned int index, unsigned int length, Buffer* buffer);

#endif