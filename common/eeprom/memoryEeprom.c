#include "memoryEeprom.h"
#include "eeprom.h"

#include "../../common/error/error.h"
#include "../../common/io/buffer.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

void eepromMemoryWriteChar(Eeprom* eeprom_, unsigned long index, unsigned char value) {
    if (index > eeprom_->maxIndex) {
        writeError(EEPROM_OUT_OF_BOUNDS);
        return;
    }
    char* sPointer = (char*)eeprom_->object;
    sPointer += index;
    *sPointer = value;
}

char eepromMemoryReadChar(Eeprom* eeprom_, unsigned long index) {
    if (index > eeprom_->maxIndex) {
        writeError(EEPROM_OUT_OF_BOUNDS);
        return 0;
    }
    char* sPointer = (char*)eeprom_->object;
    sPointer += index;
    char result = *sPointer;
    return result;
    
}

void eepromMemoryReadBlock(Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer) {
    // Find a better implementation
    unsigned long i;
    for (i = index; i < index + length; i++) {
        char value = eeprom_->eepromReadChar(eeprom_, i);
        append(getOutputStream(buffer), value);
    }
}

void eepromMemoryWriteBlock(Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer) {
    // Find a better implementation
    unsigned long i;
    for (i = index; i < index + length; i++) {
        InputStream* inputStream = getInputStream(buffer);
        char value = readBinaryChar(inputStream);
        eeprom_->eepromWriteChar(eeprom_, i, value);
    }
}

void initEepromMemory(Eeprom* memoryEeprom, char(*valuesArray)[], unsigned int maxIndex) {
    initEeprom(memoryEeprom, maxIndex, eepromMemoryWriteChar, eepromMemoryReadChar, eepromMemoryReadBlock, eepromMemoryWriteBlock, NULL, NULL, valuesArray);
}
