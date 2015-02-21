#ifndef EEPROM_FILE
#define EEPROM_FILE

#include "../../../common/eeprom/eeprom.h"

/**
 * The type of drive which relies on an EEPROM
 */
#define EEPROM_DRIVE_NUMBER 0

#define EEPROM_SECTOR_SIZE  512
#define EEPROM_SECTOR_COUNT 128

void initEepromFile(Eeprom* eepromParam);

#endif
