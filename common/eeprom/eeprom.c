#include "eeprom.h"

void initEeprom(Eeprom* eeprom, 
                EepromWriteIntFunction* eepromWriteInt,
                EepromReadIntFunction* eepromReadInt,
                EepromWriteBlockFunction* eepromWriteBlock,
                EepromReadBlockFunction* eepromReadBlock) {
    eeprom->eepromWriteInt = eepromWriteInt;
    eeprom->eepromReadInt = eepromReadInt;
    eeprom->eepromWriteBlock = eepromWriteBlock;
    eeprom->eepromReadBlock = eepromReadBlock;
}

void printEepromBlock(Eeprom* eeprom, OutputStream* outputStream, long index, unsigned int length, Buffer* buffer) {
    eeprom->eepromReadBlock(eeprom, index, length, buffer);
    int i;
    for (i = 0; i < length; i++){
        char c = bufferReadChar(buffer);
        appendHex2(outputStream, c);
    }
}
