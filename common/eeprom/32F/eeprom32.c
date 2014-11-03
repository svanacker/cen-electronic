#include "../../../common/commons.h"

#include "../eeprom.h"
#include "../../../drivers/eeprom/24c16.h"

#include "../../io/outputStream.h"
#include "../../io/inputStream.h"

void eepromWriteInt(unsigned int index, signed int value){
    writeEepromInt(index,value);
    delay100us(6);
}

signed int eepromReadInt(unsigned int index){
    unsigned int data = readEepromInt(index);
    return (data);
}

void printEepromBloc (OutputStream* outputStream, long index, unsigned int length, Buffer* buffer)
{
    eepromReadBloc(index, length, buffer);
    int i;
    for (i=0; i < length; i++){
        char c = bufferReadChar(buffer);
        appendHex2(outputStream, c);
    }
}

void eepromReadBloc(unsigned int index, char length, Buffer* buffer){
    readEepromBloc(index, length, buffer);
}

void eepromWriteBloc(unsigned int index, char length, Buffer* buffer){
    writeEepromBloc(index, length , buffer);
}
