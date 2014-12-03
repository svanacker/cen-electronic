#include <peripheral/legacy/i2c_legacy.h>

#include "24c512.h"

#include "../../common/eeprom/eeprom.h"
#include "../../common/io/buffer.h"

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cCommon.h"

/**
* @private
* Calculate the chip address to select
* @param index the index to calculate the chip Address
* @return the chip address to select
*/
unsigned long get24C512BlockAddress (unsigned long index) {
    unsigned long blocAddress = ST24C512_ADDRESS_0;

    // step of 64 KBytes
    if (index < 0x010000 ) {
    } else if (index < 0x020000) {
        blocAddress = ST24C512_ADDRESS_1;
    } else if (index < 0x030000) {
        blocAddress = ST24C512_ADDRESS_2;
    } else if (index < 0x040000) {
        blocAddress = ST24C512_ADDRESS_3;
    } else if (index < 0x050000) {
        blocAddress = ST24C512_ADDRESS_4;
    } else if (index < 0x060000) {
        blocAddress = ST24C512_ADDRESS_5;
    } else if (index < 0x070000) {
        blocAddress = ST24C512_ADDRESS_6;
    } else if (index < 0x080000) {
        blocAddress = ST24C512_ADDRESS_7;
    } else {
        // ERROR  TO DO
    }
    return blocAddress;
}

/**
* @private
* Calculate the address in the chip to select.
* @param index the index to calculate the address
* @return the address result
*/
unsigned long get24C512Address(unsigned long index) {
    unsigned long address = index;

    // step of 64 KBytes
    if (index < 0x010000 ) {
    } else if (index < 0x020000) {
        address -= 0x010000;
    } else if (index < 0x030000) {
        address -= 0x020000;
    } else if (index < 0x040000) {
        address -= 0x030000;
    } else if (index < 0x050000) {
        address -= 0x040000;
    } else if (index < 0x060000) {
        address -= 0x050000;
    } else if (index < 0x070000) {
        address -= 0x060000;
    } else if (index < 0x080000) {
        address -= 0x070000;
    } else {
        // ERROR  TO DO
    }
    return address;
}

/**
 * Implementation of the write Function of the 24C512 chip.
 * @see eeprom.h
 * @private
 */
void _writeEeprom24C512Int(Eeprom* eeprom_, unsigned long index, signed int value){
    portableMasterWaitSendI2C();
    portableStartI2C();
    WaitI2C();
    unsigned int blockAddress = get24C512BlockAddress(index);
    portableMasterWriteI2C(blockAddress);
    WaitI2C();

    unsigned int msbaddress = index >> 8;
    unsigned int lsbaddress = index & 0xFFFF;

    portableMasterWriteI2C(msbaddress);
    WaitI2C();
    portableMasterWriteI2C(lsbaddress);
    WaitI2C();

    portableMasterWriteI2C(value);
    WaitI2C();
    portableStopI2C();
    WaitI2C();
}

/**
 * Implementation of the read Function of the 24C16 chip.
 * @see eeprom.h
 * @private
 */
signed int _readEeprom24C512Int(Eeprom* eeprom_, unsigned long index){
    portableMasterWaitSendI2C();

    portableMasterWaitSendI2C();
    portableStartI2C();
    WaitI2C();
    unsigned int blockAddress = get24C512BlockAddress(index);
    portableMasterWriteI2C(blockAddress);
    WaitI2C();

    unsigned int msbaddress = index >> 8;
    unsigned int lsbaddress = index & 0xFFFF;

    portableMasterWriteI2C(msbaddress);
    WaitI2C();
    portableMasterWriteI2C(lsbaddress);
    WaitI2C();

    // read one data
    portableStartI2C();
    WaitI2C();

    portableMasterWriteI2C(blockAddress | 0x01);
    WaitI2C();

    char data = portableMasterReadI2C();
    portableNackI2C();
    WaitI2C();

    portableStopI2C();
    WaitI2C();
    return data;
}

/**
 * Implementation of the write Function of the 24C512 chip.
 * @see eeprom.h
 * @private
 */
void _writeEeprom24C512Block (Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer) {
    int blockAddress = get24C512BlockAddress(index);
    int address = get24C512Address(index);
    portableMasterWaitSendI2C();
    portableStartI2C();
    WaitI2C();
    portableMasterWriteI2C(blockAddress);
    WaitI2C();
    portableMasterWriteI2C(address);
    WaitI2C();
    int i;
    for (i = 0; i <(length) ; i++) {
        char c = bufferReadChar(buffer);
        portableMasterWriteI2C(c);
        WaitI2C();
    }
    portableStopI2C();
    WaitI2C();
}


/**
 * Implementation of the readBlock Function of the 24C512 chip.
 * @see eeprom.h
 * @private
 */
void _readEeprom24C512Block(Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer){
   portableMasterWaitSendI2C();

    portableMasterWaitSendI2C();
    portableStartI2C();
    WaitI2C();
    unsigned int blockAddress = get24C512BlockAddress(index);
    portableMasterWriteI2C(blockAddress);
    WaitI2C();

    unsigned int msbaddress = index >> 8;
    unsigned int lsbaddress = index & 0xFFFF;

    portableMasterWriteI2C(msbaddress);
    WaitI2C();
    portableMasterWriteI2C(lsbaddress);
    WaitI2C();

    // read the data
    portableStartI2C();
    WaitI2C();

    portableMasterWriteI2C(blockAddress | 0x01);

    int i;
    for (i = 0; i < length - 1; i++) {
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

void init24C512Eeprom(Eeprom* eeprom_) {
    initEeprom(eeprom_, _writeEeprom24C512Int, _readEeprom24C512Int, _writeEeprom24C512Block, _readEeprom24C512Block);
}
