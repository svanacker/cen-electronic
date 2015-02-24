#ifdef PROG_32
    #include <peripheral/legacy/i2c_legacy.h>
#endif
#ifdef PROG_30
    #include <i2c.h>
#endif

#include "24c16.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/eeprom/eeprom.h"
#include "../../common/error/error.h"
#include "../../common/io/buffer.h"

#include "../../common/i2c/master/i2cMaster.h"

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cCommon.h"

#define EEPROM_24C16_MAX_INDEX        0x3FFF

I2cBus* _24C16GetI2c(Eeprom* eeprom_) {
    I2cBus* result = (I2cBus*) eeprom_->object;

    return result;
}

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
void _writeEeprom24C16Char(Eeprom* eeprom_, unsigned long index, char value){
    I2cBus* i2cBus = _24C16GetI2c(eeprom_);
    portableMasterWaitSendI2C(i2cBus);
    portableStartI2C(i2cBus);
    WaitI2C(i2cBus);
    unsigned int blockAddress = get24C16BlockAddress(index);
    portableMasterWriteI2C(i2cBus, blockAddress);
    WaitI2C(i2cBus);

    unsigned int address = get24C16Address(index);
    portableMasterWriteI2C(i2cBus, address);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBus, value);
    WaitI2C(i2cBus);
    portableStopI2C(i2cBus);
    WaitI2C(i2cBus);
    
    delay100us(4);  // delay <=3 don't write correctly if we write several times
}

/**
 * Implementation of the read Function of the 24C16 chip.
 * @see eeprom.h
 * @private
 */
char _readEeprom24C16Char(Eeprom* eeprom_, unsigned long index){
    I2cBus* i2cBus = _24C16GetI2c(eeprom_);
    portableMasterWaitSendI2C(i2cBus);
     // Set the register command
    int blockAddress = get24C16BlockAddress(index);
    int address = get24C16Address(index);
    i2cMasterWriteChar(i2cBus, blockAddress, address);

    // read one data
    portableStartI2C(i2cBus);
    WaitI2C(i2cBus);

    portableMasterWriteI2C(i2cBus, blockAddress | 0x01);
    WaitI2C(i2cBus);

    char data = portableMasterReadI2C(i2cBus);
    portableNackI2C(i2cBus);
    WaitI2C(i2cBus);

    portableStopI2C(i2cBus);
    WaitI2C(i2cBus);
    return data;
}

/**
 * Implementation of the write Function of the 24C16 chip.
 * @see eeprom.h
 * @private
 */
void _writeEeprom24C16Block (Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer) {
    I2cBus* i2cBus = _24C16GetI2c(eeprom_);
    int blockAddress = get24C16BlockAddress(index);
    int address = get24C16Address(index);
    portableMasterWaitSendI2C(i2cBus);
    portableStartI2C(i2cBus);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBus, blockAddress);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBus, address);
    WaitI2C(i2cBus);
    int i;
    for (i = 0; i <(length) ; i++) {
        char c = bufferReadChar(buffer);
        portableMasterWriteI2C(i2cBus, c);
        WaitI2C(i2cBus);
    }
    portableStopI2C(i2cBus);
    WaitI2C(i2cBus);
}


/**
 * Implementation of the readBlock Function of the 24C16 chip.
 * @see eeprom.h
 * @private
 */
void _readEeprom24C16Block(Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer){
    I2cBus* i2cBus = _24C16GetI2c(eeprom_);
    // Set the register command
    int blockAddress = get24C16BlockAddress(index);
    int address = get24C16Address(index);
    i2cMasterWriteChar(i2cBus, blockAddress, address);

    // read the data
    portableStartI2C(i2cBus);
    WaitI2C(i2cBus);

    portableMasterWriteI2C(i2cBus, address | 0x01);

    int i;
    for (i = 0; i < length - 1; i++) {
        char c = portableMasterReadI2C(i2cBus);
        portableAckI2C(i2cBus);
        WaitI2C(i2cBus);
        bufferWriteChar(buffer, c);
    }
    char c = portableMasterReadI2C(i2cBus);
    portableNackI2C(i2cBus);
    WaitI2C(i2cBus);
    bufferWriteChar(buffer, c);
    portableStopI2C(i2cBus);
    WaitI2C(i2cBus);
}


void dumpEeprom(Eeprom* eeprom_) {
    if (eeprom_ == NULL) {
        writeError(UNIMPLETEMENTED_EXCEPTION);
        return;
    }  
}

void init24C16Eeprom(Eeprom* eeprom_, I2cBus* i2cBus) {
    initEeprom(eeprom_, EEPROM_24C16_MAX_INDEX, _writeEeprom24C16Char, _readEeprom24C16Char, _writeEeprom24C16Block, _readEeprom24C16Block, (int*) i2cBus);
}
