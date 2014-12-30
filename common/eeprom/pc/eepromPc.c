#include "eepromPc.h"
#include "../eeprom.h"

#include "../../../common/error/error.h"
#include "../../../common/io/buffer.h"
#include "../../../common/io/printWriter.h"

#define EEPROM_PC_MAX_INDEX        0xFFFF

static signed int eepromPc[EEPROM_PC_MAX_INDEX + 1];

void eepromPcWriteInt(Eeprom* eeprom_, unsigned long index, signed int value) {
    if (index > EEPROM_PC_MAX_INDEX) {
        writeError(EEPROM_OUT_OF_BOUNDS);
    }
    eepromPc[index] = value;
}

signed int eepromReadInt(Eeprom* eeprom_, unsigned long index) {
    if (index > EEPROM_PC_MAX_INDEX) {
        writeError(EEPROM_OUT_OF_BOUNDS);
        return 0;
    }
    signed int result = eepromPc[index];
    return result;
}

void eepromReadBlock(Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer) {
    unsigned long i;
    for (i = index; i < index + length; i++) {
        signed int value = eepromReadInt(eeprom_, i);
        // TODO
        writeError(UNIMPLETEMENTED_EXCEPTION);
    }
}

void eepromWriteBlock(Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer) {
    unsigned long i;
    for (i = index; i < index + length; i++) {
        signed int value = eepromReadInt(eeprom_, i);
        // TODO
        writeError(UNIMPLETEMENTED_EXCEPTION);
    }

}

void initEepromPc(Eeprom* eepromPc) {
    initEeprom(eepromPc, EEPROM_PC_MAX_INDEX, eepromPcWriteInt, eepromReadInt, eepromReadBlock, eepromWriteBlock);
}
