#ifndef EEPROM_H
#define EEPROM_H

/** Define a value which has been erased by programmation. */
#define ERASED_VALUE_EEPROM 		0xFFFF

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

#endif




