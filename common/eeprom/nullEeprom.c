#include "nullEeprom.h"
#include "eeprom.h"

#include <stdlib.h>

#include "../../common/error/error.h"

void nullEepromWriteChar(Eeprom* eeprom_, unsigned long index, char value) {
    // DO NOTHING
}

char nullEepromReadChar(Eeprom* eeprom_, unsigned long index) {
    return 0;
}

void nullEepromReadBlock(Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer) {
    writeError(UNIMPLETEMENTED_EXCEPTION);
}

void nullEepromWriteBlock(Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer) {
    writeError(UNIMPLETEMENTED_EXCEPTION);
}

void initNullEeprom(Eeprom* nullEeprom) {
    initEeprom(nullEeprom, 35535, nullEepromWriteChar, nullEepromReadChar, nullEepromWriteBlock, nullEepromReadBlock, NULL);
}
