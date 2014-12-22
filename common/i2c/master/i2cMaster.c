#include "i2cMaster.h"
#include "../i2cCommon.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/i2c/i2cCommon.h"
#include "../../../common/io/buffer.h"

void i2cMasterWriteBuffer(unsigned char address, Buffer* buffer) {
    portableMasterWaitSendI2C();
    // Wait till Start sequence is completed
    WaitI2C();

    portableStartI2C();
    WaitI2C();
    // Adress
    portableMasterWriteI2C(address);
    WaitI2C();

    int count = getBufferElementsCount(buffer);
    int i;
    for (i = 0; i < count; i++) {
        char c = bufferReadChar(buffer);
        portableMasterWriteI2C(c);
        WaitI2C();
    }

    portableStopI2C();
}

void i2cMasterWriteChar(unsigned char address, unsigned char c) {
    // We append to a buffer
    portableStartI2C();
    // Wait till Start sequence is completed
    WaitI2C();

    // Adress
    portableMasterWriteI2C(address);
    WaitI2C();

    // Data
    portableMasterWriteI2C(c);
    WaitI2C();

    portableStopI2C();
    WaitI2C();
}

unsigned char i2cMasterReadChar(unsigned char address) {
    portableStartI2C();
    WaitI2C();

    // send the address again with read bit
    portableMasterWriteI2C(address | 0x01);
    WaitI2C();

    unsigned char data = portableMasterReadI2C();
    WaitI2C();

    portableStopI2C();
    WaitI2C();
    return data;
}

unsigned char i2cMasterReadRegisterValue(unsigned char address, unsigned char commandRegister) {
    // Set the register command
    WaitI2C();
    portableStartI2C();

    WaitI2C();
    portableMasterWaitSendI2C();

    WaitI2C();
    // send the address
    portableMasterWriteI2C(address);

    WaitI2C();
    // send the register
    portableMasterWriteI2C(commandRegister);

    WaitI2C();
    portableStopI2C();

    WaitI2C();
    // Read the register command
    portableStartI2C();

    WaitI2C();
    portableMasterWaitSendI2C();
    // send the address again with read bit
    portableMasterWriteI2C(address | 0x01);
    WaitI2C();
    // read the data
    char data = portableMasterReadI2C();
    portableStopI2C();
    return data;
}

void i2cMasterRegisterReadBuffer(unsigned char address, unsigned char reg, unsigned char length, Buffer* buffer){
    // Set the register command
    i2cMasterWriteChar(address, reg);

    // read the data
    portableStartI2C();
    WaitI2C();

    portableMasterWriteI2C(address | 0x01);

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

void i2cMasterReadBuffer(unsigned char address, unsigned char length, Buffer* buffer){
    portableStartI2C();
    WaitI2C();
    portableMasterWriteI2C(address );

    // read the data
    portableStartI2C();
    WaitI2C();
    portableMasterWriteI2C(address | 0x01);

    int i;
    for (i = 0; i <length ; i++) {
        char c = portableMasterReadI2C();
        portableAckI2C();
        WaitI2C();
        bufferWriteChar(buffer, c);
    }
    portableStopI2C();
    WaitI2C();
}

