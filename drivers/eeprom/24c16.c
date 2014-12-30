#include <peripheral/legacy/i2c_legacy.h>

#include "24c16.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/eeprom/eeprom.h"
#include "../../common/error/error.h"
#include "../../common/io/buffer.h"

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cCommon.h"

#define EEPROM_24C16_MAX_INDEX        0x3FFF

/**
* @private
* Calculate the chip address to select
* @param index the index to calculate the chip Address
* @return the chip address to select
*/
unsigned long get24C16BlockAddress (unsigned long index) {
    unsigned long blocAddress = ST24C16_ADDRESS_0;

    // step of 2 KBytes
    if (index < 0x0800 ) {
    } else if (index < 0x1000) {
        blocAddress = ST24C16_ADDRESS_1;
    } else if (index < 0x1800) {
        blocAddress = ST24C16_ADDRESS_2;
    } else if (index < 0x2000) {
        blocAddress = ST24C16_ADDRESS_3;
    } else if (index < 0x2800) {
        blocAddress = ST24C16_ADDRESS_4;
    } else if (index < 0x3000) {
        blocAddress = ST24C16_ADDRESS_5;
    } else if (index < 0x3800) {
        blocAddress = ST24C16_ADDRESS_6;
    } else if (index < 0x4000) {
        blocAddress = ST24C16_ADDRESS_7;
    } else {
       writeError(EEPROM_OUT_OF_BOUNDS);
    }
    return blocAddress;
}

/**
* @private
* Calculate the address in the chip to select.
* @param index the index to calculate the address
* @return the address result
*/
unsigned long get24C16Address(unsigned long index) {
    unsigned long address = index;
    
    // step of 2 KBytes
    if (index < 0x0800 ) {
    } else if (index < 0x1000) {
        address -= 0x0800;
    } else if (index < 0x1800) {
        address -= 0x1000;
    } else if (index < 0x2000) {
        address -= 0x1800;
    } else if (index < 0x2800) {
        address -= 0x2000;
    } else if (index < 0x3000) {
        address -= 0x2800;
    } else if (index < 0x3800) {
        address -= 0x3000;
    } else if (index < 0x4000) {
        address -= 0x3800;
    } else {
        writeError(EEPROM_OUT_OF_BOUNDS);
    }
    return address;
}

/**
 * Implementation of the write Function of the 24C16 chip.
 * @see eeprom.h
 * @private
 */
void _writeEeprom24C16Int(Eeprom* eeprom_, unsigned long index, signed int value){
    portableMasterWaitSendI2C();
    portableStartI2C();
    WaitI2C();
    unsigned int blockAddress = get24C16BlockAddress(index);
    portableMasterWriteI2C(blockAddress);
    WaitI2C();

    unsigned int address = get24C16Address(index);
    portableMasterWriteI2C(address);
    WaitI2C();
    portableMasterWriteI2C(value);
    WaitI2C();
    portableStopI2C();
    WaitI2C();
    
    delay100us(4);  // delay <=3 don't write correctly if we write several times
}

/**
 * Implementation of the read Function of the 24C16 chip.
 * @see eeprom.h
 * @private
 */
signed int _readEeprom24C16Int(Eeprom* eeprom_, unsigned long index){
    portableMasterWaitSendI2C();
     // Set the register command
    int blockAddress = get24C16BlockAddress(index);
    int address = get24C16Address(index);
    i2cMasterWriteChar(blockAddress, address);

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
 * Implementation of the write Function of the 24C16 chip.
 * @see eeprom.h
 * @private
 */
void _writeEeprom24C16Block (Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer) {
    int blockAddress = get24C16BlockAddress(index);
    int address = get24C16Address(index);
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
 * Implementation of the readBlock Function of the 24C16 chip.
 * @see eeprom.h
 * @private
 */
void _readEeprom24C16Block(Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer){
    // Set the register command
    int blockAddress = get24C16BlockAddress(index);
    int address = get24C16Address(index);
    i2cMasterWriteChar(blockAddress, address);

    // read the data
    portableStartI2C();
    WaitI2C();

    portableMasterWriteI2C(address | 0x01);

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

void init24C16Eeprom(Eeprom* eeprom_) {
    initEeprom(eeprom_, EEPROM_24C16_MAX_INDEX, _writeEeprom24C16Int, _readEeprom24C16Int, _writeEeprom24C16Block, _readEeprom24C16Block);
}
