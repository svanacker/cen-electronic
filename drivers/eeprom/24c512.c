#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#include <plib.h>

#include "24c512.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/master/i2cMaster.h"

#include "../../common/eeprom/eeprom.h"
#include "../../common/eeprom/eepromType.h"
#include "../../common/error/error.h"
#include "../../common/io/buffer.h"

#include "../../common/i2c/i2cCommon.h"

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cCommon.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/outputStream.h"

I2cBusConnection* _24c512GetI2cBusConnection(Eeprom* eeprom_) {
    I2cBusConnection* result = (I2cBusConnection*) eeprom_->object;

    return result;
}

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
        writeError(EEPROM_OUT_OF_BOUNDS);
    }
    return address;
}

/**
 * Implementation of the write Function of the 24C512 chip.
 * @see eeprom.h
 * @private
 */
void _writeEeprom24C512Char(Eeprom* eeprom_, unsigned long index, unsigned char value) {
    I2cBusConnection* i2cBusConnection = _24c512GetI2cBusConnection(eeprom_);

    portableMasterWaitSendI2C(i2cBusConnection);
    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    unsigned int blockAddress = get24C512BlockAddress(index);
    portableMasterWriteI2C(i2cBusConnection, blockAddress);
    WaitI2cBusConnection(i2cBusConnection);

    unsigned int msbaddress = index >> 8;
    unsigned int lsbaddress = index & 0xFFFF;

    portableMasterWriteI2C(i2cBusConnection, msbaddress);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, lsbaddress);
    WaitI2cBusConnection(i2cBusConnection);

    portableMasterWriteI2C(i2cBusConnection, value);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    delayMilliSecs(3); // in Datasheet, write needs 5 milliSeconds, but it seems that 1ms is enough
}

/**
 * Implementation of the read Function of the 24C16 chip.
 * @see eeprom.h
 * @private
 */
unsigned char _readEeprom24C512Char(Eeprom* eeprom_, unsigned long index) {
    I2cBusConnection* i2cBusConnection = _24c512GetI2cBusConnection(eeprom_);

    portableMasterWaitSendI2C(i2cBusConnection);

    portableMasterWaitSendI2C(i2cBusConnection);
    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    unsigned int blockAddress = get24C512BlockAddress(index);
    portableMasterWriteI2C(i2cBusConnection, blockAddress);
    WaitI2cBusConnection(i2cBusConnection);

    unsigned int msbaddress = index >> 8;
    unsigned int lsbaddress = index & 0xFFFF;

    portableMasterWriteI2C(i2cBusConnection, msbaddress);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, lsbaddress);
    WaitI2cBusConnection(i2cBusConnection);

    // read one data
    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);

    portableMasterWriteI2C(i2cBusConnection, blockAddress | 0x01);
    WaitI2cBusConnection(i2cBusConnection);

    char data = portableMasterReadI2C(i2cBusConnection);
    portableMasterNackI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);

    portableMasterStopI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    return data;
}

/**
 * Implementation of the write Function of the 24C512 chip.
 * @see eeprom.h
 * @private
 */
void _writeEeprom24C512Block (Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer) {
    I2cBusConnection* i2cBusConnection = _24c512GetI2cBusConnection(eeprom_);

    int blockAddress = get24C512BlockAddress(index);
    int address = get24C512Address(index);
    portableMasterWaitSendI2C(i2cBusConnection);
    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, blockAddress);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, address);
    WaitI2cBusConnection(i2cBusConnection);
    int i;
    for (i = 0; i <(length) ; i++) {
        char c = bufferReadChar(buffer);
        portableMasterWriteI2C(i2cBusConnection, c);
        WaitI2cBusConnection(i2cBusConnection);
    }
    portableMasterStopI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
}

/**
 * Implementation of the readBlock Function of the 24C512 chip.
 * @see eeprom.h
 * @private
 */
void _readEeprom24C512Block(Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer){
    I2cBusConnection* i2cBusConnection = _24c512GetI2cBusConnection(eeprom_);

    portableMasterWaitSendI2C(i2cBusConnection);

    portableMasterWaitSendI2C(i2cBusConnection);
    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    unsigned int blockAddress = get24C512BlockAddress(index);
    portableMasterWriteI2C(i2cBusConnection, blockAddress);
    WaitI2cBusConnection(i2cBusConnection);

    unsigned int msbaddress = index >> 8;
    unsigned int lsbaddress = index & 0xFFFF;

    portableMasterWriteI2C(i2cBusConnection, msbaddress);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, lsbaddress);
    WaitI2cBusConnection(i2cBusConnection);

    // read the data
    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);

    portableMasterWriteI2C(i2cBusConnection, blockAddress | 0x01);

    int i;
    for (i = 0; i < length - 1; i++) {
        char c = portableMasterReadI2C(i2cBusConnection);
        portableMasterAckI2C(i2cBusConnection);
        WaitI2cBusConnection(i2cBusConnection);
        bufferWriteChar(buffer, c);
    }
    char c = portableMasterReadI2C(i2cBusConnection);
    portableMasterNackI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    bufferWriteChar(buffer, c);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
}

void _loadEeprom24C512(Eeprom* eeprom_) {
    if (eeprom_ == NULL) {
        writeError(UNIMPLETEMENTED_EXCEPTION);
        return;
    }  
}

void _dumpEeprom24C512(Eeprom* eeprom_) {
    if (eeprom_ == NULL) {
        writeError(UNIMPLETEMENTED_EXCEPTION);
        return;
    }  
}

void init24C512Eeprom(Eeprom* eeprom_, I2cBusConnection* i2cBusConnection) {
    initEeprom(eeprom_,
               EEPROM_TYPE_HARDWARE,
               EEPROM_24C512_MAX_INDEX,
               _writeEeprom24C512Char,
               _readEeprom24C512Char,
               _writeEeprom24C512Block,
               _readEeprom24C512Block,
               _loadEeprom24C512,
               _dumpEeprom24C512,
                 (int*) i2cBusConnection);
}
