#ifndef NULL_EEPROM_H
#define NULL_EEPROM_H

#include "eeprom.h"

/**
 * Initializes a fake Eeprom which returns always 0 and does nothing when writing.
 * It is useful for test
 * @param nullEeprom a pointer on eeprom object
 */
void initNullEeprom(Eeprom* nullEeprom);

#endif

