#include "../../../common/commons.h"

#include "../eeprom.h"

#include "../../io/outputStream.h"
#include "../../io/inputStream.h"

//void my_eeprom_write_int(unsigned int index, signed int value) {
    // TODO !!!!
//}

//signed int my_eeprom_read_int(unsigned int index) {
    // TODO !!!!
//    return 0;
//}

void printEepromBloc (OutputStream* outputStream,long index, unsigned int length, Buffer* buffer)
{
    my_eeprom_read_bloc(index, length, buffer);
    int i;
    for (i=0; i < length; i++){
        appendHex2(outputStream, bufferReadChar(buffer));
    }
}

void writeEepromBloc (InputStream* inputStream,long index, unsigned int length, Buffer* buffer){
    
}


