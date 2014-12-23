#include "nullEeprom.h"
#include "eeprom.h"

#include "../../common/error/error.h"

void nullEepromWriteInt(Eeprom* eeprom_, unsigned long index, signed int value) {
    // DO NOTHING
}

signed int nullEepromReadInt(Eeprom* eeprom_, unsigned long index) {
    return 0;
}

void nullEepromReadBlock(Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer) {
    writeError(UNIMPLETEMENTED_EXCEPTION);
}

void nullEepromWriteBlock(Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer) {
    writeError(UNIMPLETEMENTED_EXCEPTION);
}

void initNullEeprom(Eeprom* nullEeprom) {
    initEeprom(nullEeprom, 35535, nullEepromWriteInt, nullEepromReadInt, nullEepromWriteBlock, nullEepromReadBlock);
}
