#ifndef ST24C16_H
#define    ST24C16_H

#include "../../common/io/buffer.h"
#include "../../common/eeprom/eeprom.h"

/**
 * Initialize a type of eeprom : 24C16
 * @param eeprom a pointer of eeprom type.
 */
void init24C16Eeprom(Eeprom* eeprom_);

#endif