#include "eeprom.h"

void initEeprom(Eeprom* eeprom_,
                EepromWriteIntFunction* eepromWriteInt,
                EepromReadIntFunction* eepromReadInt,
                EepromWriteBlockFunction* eepromWriteBlock,
                EepromReadBlockFunction* eepromReadBlock) {
    eeprom_->eepromWriteInt = eepromWriteInt;
    eeprom_->eepromReadInt = eepromReadInt;
    eeprom_->eepromWriteBlock = eepromWriteBlock;
    eeprom_->eepromReadBlock = eepromReadBlock;
}

void printEepromBlock(Eeprom* eeprom_, OutputStream* outputStream, long index, unsigned int length, Buffer* buffer) {
    eeprom_->eepromReadBlock(eeprom_, index, length, buffer);
    int i;
    for (i = 0; i < length; i++){
        char c = bufferReadChar(buffer);
        appendHex2(outputStream, c);
    }
}
