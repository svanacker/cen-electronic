#ifndef EEPROM_H
#define EEPROM_H

#include "../../common/io/buffer.h"

/** Define a value which has been erased by programmation. */
#define ERASED_VALUE_EEPROM         0xFFFF

/**
 * Writes a value at the specified index into EEPROM.
 * @param index the index of the WORD in the EEPROM table. Index 0 should not be used because this value is erased when reprogramming the device.
 * @param value the value to store
 */
void my_eeprom_write_int(unsigned int index, signed int value);

/**
 * Reads the value from the EEPROM at the given index.
 * @param index the index of the WORD value to read
 * @return the WORD value as a signed int
 */
signed int my_eeprom_read_int(unsigned int index);

/** BY JEROME
 * Read values from the EEPROM device.
 * Slave will return all values and store them in the buffer
 * @param index          the random address to read
 * @param length         the number of data to read
 * @param Buffer* buffer the buffer
 */
void my_eeprom_read_bloc(unsigned int index, char length, Buffer* buffer);

/** BY JEROME
 * Print  the values of the buffer on the outputStream from the EEPROM device.
 * Slave will return all values and print them on the outputStream
 * @param OutputStream* outputStream    the outputStream
 * @param index                         the random address to read
 * @param length                        the number of data to read
 * @param Buffer* buffer                the buffer
 */

void printEepromBloc (OutputStream* outputStream,long index, unsigned int length, Buffer* buffer);

/** BY JEROME
 * Write  the values of the inputStream on the the EEPROM device.
 * @param InputStream* inputStream      the inputStream
 * @param index                         the random address to read
 * @param length                        the number of data to read
 * @param Buffer* buffer                the buffer
 */

void writeEepromBloc (InputStream* inputStream,long index, unsigned int length, Buffer* buffer);

#endif