#include "../../../common/commons.h"

#include "../eeprom.h"
#include "../../../drivers/eeprom/24c16.h"

#include "../../io/outputStream.h"
#include "../../io/inputStream.h"

void my_eeprom_write_int(unsigned int index, signed int value){
    writeEepromInt(index,value);
    delay100us(6);
}

signed int my_eeprom_read_int(unsigned int index){
    unsigned int data = readEepromInt(index);
    return (data);
}

void printEepromBloc (OutputStream* outputStream,long index, unsigned int length, Buffer* buffer)
{
    my_eeprom_read_bloc(index, length, buffer);
    int i;
    for (i=0; i < length; i++){
        appendHex2(outputStream, bufferReadChar(buffer));
    }
}

void my_eeprom_read_bloc(unsigned int index, char length, Buffer* buffer){
    readEepromBloc(index, length, buffer);
}

void my_eeprom_write_bloc(unsigned int index, char length, Buffer* buffer){
    writeEepromBloc(index, length , buffer);
}
