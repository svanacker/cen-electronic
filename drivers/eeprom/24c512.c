#include <peripheral/legacy/i2c_legacy.h>

#include "24c512.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/master/i2cMaster.h"

#include "../../common/eeprom/eeprom.h"
#include "../../common/error/error.h"
#include "../../common/io/buffer.h"

#include "../../common/i2c/i2cCommon.h"

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cCommon.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/outputStream.h"

I2cBus* _24c512GetI2c(Eeprom* eeprom_) {
    I2cBus* result = (I2cBus*) eeprom_->object;

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
void _writeEeprom24C512Char(Eeprom* eeprom_, unsigned long index, char value) {
    /*
    OutputStream* outputStream = getDebugOutputStreamLogger();
    appendStringAndDec(outputStream, "write Eeprom index=", index);
    appendStringAndDec(outputStream, ", value=", value);
    appendCRLF(outputStream);
    */

    I2cBus* i2cBus = _24c512GetI2c(eeprom_);
    portableMasterWaitSendI2C(i2cBus);
    portableStartI2C(i2cBus);
    WaitI2C(i2cBus);
    unsigned int blockAddress = get24C512BlockAddress(index);
    portableMasterWriteI2C(i2cBus, blockAddress);
    WaitI2C(i2cBus);

    unsigned int msbaddress = index >> 8;
    unsigned int lsbaddress = index & 0xFFFF;

    portableMasterWriteI2C(i2cBus, msbaddress);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBus, lsbaddress);
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
char _readEeprom24C512Char(Eeprom* eeprom_, unsigned long index) {
    /*
    OutputStream* outputStream = getDebugOutputStreamLogger();
    appendStringAndDec(outputStream, "read Eeprom index=", index);
    appendCRLF(outputStream);
    */
    I2cBus* i2cBus = _24c512GetI2c(eeprom_);

    portableMasterWaitSendI2C(i2cBus);

    portableMasterWaitSendI2C(i2cBus);
    portableStartI2C(i2cBus);
    WaitI2C(i2cBus);
    unsigned int blockAddress = get24C512BlockAddress(index);
    portableMasterWriteI2C(i2cBus, blockAddress);
    WaitI2C(i2cBus);

    unsigned int msbaddress = index >> 8;
    unsigned int lsbaddress = index & 0xFFFF;

    portableMasterWriteI2C(i2cBus, msbaddress);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBus, lsbaddress);
    WaitI2C(i2cBus);

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
 * Implementation of the write Function of the 24C512 chip.
 * @see eeprom.h
 * @private
 */
void _writeEeprom24C512Block (Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer) {
    I2cBus* i2cBus = _24c512GetI2c(eeprom_);

    int blockAddress = get24C512BlockAddress(index);
    int address = get24C512Address(index);
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
 * Implementation of the readBlock Function of the 24C512 chip.
 * @see eeprom.h
 * @private
 */
void _readEeprom24C512Block(Eeprom* eeprom_, unsigned long index, unsigned int length, Buffer* buffer){
   I2cBus* i2cBus = _24c512GetI2c(eeprom_);

   portableMasterWaitSendI2C(i2cBus);

    portableMasterWaitSendI2C(i2cBus);
    portableStartI2C(i2cBus);
    WaitI2C(i2cBus);
    unsigned int blockAddress = get24C512BlockAddress(index);
    portableMasterWriteI2C(i2cBus, blockAddress);
    WaitI2C(i2cBus);

    unsigned int msbaddress = index >> 8;
    unsigned int lsbaddress = index & 0xFFFF;

    portableMasterWriteI2C(i2cBus, msbaddress);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBus, lsbaddress);
    WaitI2C(i2cBus);

    // read the data
    portableStartI2C(i2cBus);
    WaitI2C(i2cBus);

    portableMasterWriteI2C(i2cBus, blockAddress | 0x01);

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

void dumpEepromToFile(Eeprom* eeprom_) {
    if (eeprom_ == NULL) {
        writeError(UNIMPLETEMENTED_EXCEPTION);
        return;
    }  
}

void init24C512Eeprom(Eeprom* eeprom_, I2cBus* i2cBus) {
    initEeprom(eeprom_, EEPROM_24C512_MAX_INDEX, _writeEeprom24C512Char, _readEeprom24C512Char, _writeEeprom24C512Block, _readEeprom24C512Block, (int*) i2cBus);
}
