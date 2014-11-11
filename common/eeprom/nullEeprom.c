#include "nullEeprom.h"
#include "eeprom.h"

#include "../../common/error/error.h"

void nullEepromWriteInt(Eeprom* eeprom, unsigned long index, signed int value) {
    // DO NOTHING
}

signed int nullEepromReadInt(Eeprom* eeprom, unsigned long index) {
    return 0;
}

void nullEepromReadBlock(Eeprom* eeprom, unsigned long index, unsigned int length, Buffer* buffer) {
    writeError(UNIMPLETEMENTED_EXCEPTION);
}

void nullEepromWriteBlock(Eeprom* eeprom, unsigned long index, unsigned int length, Buffer* buffer) {
    writeError(UNIMPLETEMENTED_EXCEPTION);
}

void initNullEeprom(Eeprom* nullEeprom) {
    initEeprom(nullEeprom, nullEepromWriteInt, nullEepromReadInt, nullEepromWriteBlock, nullEepromReadBlock);
}
