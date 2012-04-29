#include <i2c.h>

#include "i2cMaster.h"

#include "../../../common/delay/delay30F.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/i2c/i2cCommon.h"
#include "../../../common/io/buffer.h"

void i2cMasterWriteBuffer(char address, Buffer* buffer) {
    StartI2C();
    while (I2CCONbits.SEN);
    // Wait till Start sequence is completed
    WaitI2C();

    // Adress
    MasterWriteI2C(address);
    WaitI2C();

    int count = getBufferElementsCount(buffer);
    int i;
    for (i = 0; i < count; i++) {
        char c = bufferReadChar(buffer);
        MasterWriteI2C(c);
        WaitI2C();
    }

    StopI2C();
}

void i2cMasterWriteChar(char address, char c) {
    // We append to a buffer
    StartI2C();
    // Wait till Start sequence is completed
    WaitI2C();

    // Adress
    MasterWriteI2C(c);
    WaitI2C();

    // Data
    MasterWriteI2C(c);
    WaitI2C();

    StopI2C();
}

unsigned char i2cMasterReadChar(char address) {
    //	i2cMasterWriteChar(address, I2C_SLAVE_FAKE_WRITE);
    //	delaymSec(50);
    WaitI2C();

    StartI2C();
    WaitI2C();

    // TEST
    /*
MasterWriteI2C(address);
    WaitI2C();
    StopI2C();
    WaitI2C();
    StartI2C();
    WaitI2C();
     */

    // send the address again with read bit
    MasterWriteI2C(address | 0x01);
    WaitI2C();

    unsigned char data = MasterReadI2C();

    StopI2C();
    return data;
}

unsigned char i2cMasterReadRegisterValue(char address, char commandRegister) {
    // Set the register command
    WaitI2C();
    StartI2C();
    while (I2CCONbits.SEN);
    // send the address
    MasterWriteI2C(address);
    WaitI2C();
    // send the register
    MasterWriteI2C(commandRegister);
    WaitI2C();
    StopI2C();
    WaitI2C();

    // Read the register command
    StartI2C();
    while (I2CCONbits.SEN);
    // send the address again with read bit
    MasterWriteI2C(address | 0x01);
    WaitI2C();
    // read the data
    unsigned char data = MasterReadI2C();
    StopI2C();
    return data;
}
