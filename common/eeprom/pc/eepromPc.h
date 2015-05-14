#ifndef EEPROM_PC_H
#define EEPROM_PC_H

#include "../eeprom.h"

/**
 * Initializes an eeprom linked to a file for PC.
 * @param eepromPc a pointer on eeprom object
 */
void initEepromPc(Eeprom* eepromPc, char* fileName);

#endif

