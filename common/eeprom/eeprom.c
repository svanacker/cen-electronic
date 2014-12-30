#include <stdlib.h>

#include "eeprom.h"

#include "../../common/error/error.h"
#include "../../common/io/buffer.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/outputStream.h"

void initEeprom(Eeprom* eeprom_,
                long maxIndex,
                EepromWriteIntFunction* eepromWriteInt,
                EepromReadIntFunction* eepromReadInt,
                EepromWriteBlockFunction* eepromWriteBlock,
                EepromReadBlockFunction* eepromReadBlock) {
    if (eeprom_ == NULL) {
        writeError(EEPROM_NULL);
        return;
    }            
    eeprom_->maxIndex = maxIndex;
    eeprom_->eepromWriteInt = eepromWriteInt;
    eeprom_->eepromReadInt = eepromReadInt;
    eeprom_->eepromWriteBlock = eepromWriteBlock;
    eeprom_->eepromReadBlock = eepromReadBlock;
}

long getMaxIndex(Eeprom* eeprom_) {
    if (eeprom_ == NULL) {
        writeError(EEPROM_NULL);
        return -1;
    }
    long result = eeprom_->maxIndex;
    return result;
}

void printEepromBlock(Eeprom* eeprom_, OutputStream* outputStream, long index, unsigned int length, Buffer* buffer) {
    eeprom_->eepromReadBlock(eeprom_, index, length, buffer);
    unsigned long i;
    for (i = 0; i < length; i++){
        char c = bufferReadChar(buffer);
        appendHex2(outputStream, c);
    }
}
