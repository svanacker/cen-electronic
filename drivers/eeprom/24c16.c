#include <peripheral/legacy/i2c_legacy.h>

#include "24c16.h"

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cCommon.h"
#include "../../common/io/buffer.h"

#define ST24C16_EEPROM_BUFFER_LENGTH     16
static Buffer st24C16Buffer;
static char st24C16BufferArray[ST24C16_EEPROM_BUFFER_LENGTH];
static Buffer st24C16Buffer;

unsigned int setBlocAddress (unsigned int index){
    unsigned int blocAddress = ST24C16_ADDRESS_0;

    //step of 2 koctets
    if (index < 0x0800 ) {
    } else if (index < 0x1000){
        blocAddress = ST24C16_ADDRESS_1;
    } else if (index < 0x1800){
        blocAddress = ST24C16_ADDRESS_2;
    } else if (index < 0x2000){
        blocAddress = ST24C16_ADDRESS_3;
    } else if (index < 0x2800){
        blocAddress = ST24C16_ADDRESS_4;
    } else if (index < 0x3000){
        blocAddress = ST24C16_ADDRESS_5;
    } else if (index < 0x3800){
        blocAddress = ST24C16_ADDRESS_6;
    } else if (index < 0x4000){
        blocAddress = ST24C16_ADDRESS_7;
    } else {
        //ERROR  TO DO
    }
    return blocAddress;
}

unsigned int setAddress (unsigned int index){
    unsigned int address = index;
    
    //step of 2 koctets
    if (index < 0x0800 ) {
    } else if (index < 0x1000){
        address -= 0x0800;
    } else if (index < 0x1800){
        address -= 0x1000;
    } else if (index < 0x2000){
        address -= 0x18000;
    } else if (index < 0x2800){
        address -= 0x2000;
    } else if (index < 0x3000){
        address -= 0x2800;
    } else if (index < 0x3800){
        address -= 0x3000;
    } else if (index < 0x4000){
        address -= 0x3800;
    } else {
        //ERROR  TO DO
    }
    return address;
}

void my_eeprom_write_int(unsigned int index, signed int value){
    portableMasterWaitSendI2C();
    portableStartI2C();
    WaitI2C();
    portableMasterWriteI2C(setBlocAddress(index));
    WaitI2C();
    portableMasterWriteI2C(setAddress(index));
    WaitI2C();
    portableMasterWriteI2C(value);
    WaitI2C();
    portableStopI2C();
    WaitI2C();
    delay100us(6);
}

signed int my_eeprom_read_int(unsigned int index){
    portableMasterWaitSendI2C();
     // Set the register command
    i2cMasterWriteChar(setBlocAddress(index),setAddress(index));

    // read one data
    portableStartI2C();
    WaitI2C();

    portableMasterWriteI2C(setBlocAddress(index) | 0x01);
    WaitI2C();

    char data = portableMasterReadI2C();
    portableNackI2C();
    WaitI2C();

    portableStopI2C();
    WaitI2C();
    return (data);
}

void my_eeprom_read_bloc(unsigned int index, char length, Buffer* buffer){

    // Set the register command
    i2cMasterWriteChar(setBlocAddress(index),setAddress(index));

    // read the data
    portableStartI2C();
    WaitI2C();

    portableMasterWriteI2C(setBlocAddress(index) | 0x01);

    int i;
    for (i = 0; i <(length-1) ; i++) {
        char c = portableMasterReadI2C();
        portableAckI2C();
        WaitI2C();
        bufferWriteChar(buffer, c);
    }
    char c = portableMasterReadI2C();
    portableNackI2C();
    WaitI2C();
    bufferWriteChar(buffer, c);
    portableStopI2C();
    WaitI2C();
}