
#ifndef MEMORY_EEPROM_PC_H
#define MEMORY_EEPROM_PC_H

#include "eeprom.h"

/**
 * Initializes an eeprom in memory. This can be a good replacement if there is a problem with the physical
 * eeprom
 * @param memoryEeprom the eeprom to initialize
 * @param valuesArray the values in which we store information
 * @param eepromPc a pointer on memory eeprom object
 */
void initEepromMemory(Eeprom* memoryEeprom, char(*valuesArray)[], unsigned int maxIndex);

#endif
