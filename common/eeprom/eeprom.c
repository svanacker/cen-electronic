#include <stdlib.h>
#include <stdbool.h>

#include "eeprom.h"

#include "../../common/error/error.h"
#include "../../common/io/buffer.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/outputStream.h"

void initEeprom(Eeprom* eeprom_,
                long maxIndex,
                EepromWriteCharFunction* eepromWriteChar,
                EepromReadCharFunction* eepromReadChar,
                EepromWriteBlockFunction* eepromWriteBlock,
                EepromReadBlockFunction* eepromReadBlock,
                int* object) {
    if (eeprom_ == NULL) {
        writeError(EEPROM_NULL);
        return;
    }            
    eeprom_->maxIndex = maxIndex;
    eeprom_->eepromWriteChar = eepromWriteChar;
    eeprom_->eepromReadChar = eepromReadChar;
    eeprom_->eepromWriteBlock = eepromWriteBlock;
    eeprom_->eepromReadBlock = eepromReadBlock;
    eeprom_->object = object;
}

long getMaxIndex(Eeprom* eeprom_) {
    if (eeprom_ == NULL) {
        writeError(EEPROM_NULL);
        return -1;
    }
    long result = eeprom_->maxIndex;
    return result;
}

bool isEepromInitialized(Eeprom* eeprom_) {
    if (eeprom_->eepromWriteChar == NULL || eeprom_->eepromReadChar == NULL) {
        return false;
    }
    return true;
}

void printEepromBlock(Eeprom* eeprom_, OutputStream* outputStream, long index, unsigned int length, Buffer* buffer) {
    eeprom_->eepromReadBlock(eeprom_, index, length, buffer);
    unsigned long i;
    for (i = 0; i < length; i++){
        char c = bufferReadChar(buffer);
        appendHex2(outputStream, c);
    }
}
