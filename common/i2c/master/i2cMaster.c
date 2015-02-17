#include "i2cMaster.h"
#include "../i2cCommon.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/i2c/i2cCommon.h"
#include "../../../common/io/buffer.h"

void i2cMasterWriteBuffer(I2cBus* i2cBus, unsigned char address, Buffer* buffer) {
    portableMasterWaitSendI2C(i2cBus);
    // Wait till Start sequence is completed
    WaitI2C(i2cBus);

    portableStartI2C(i2cBus);
    WaitI2C(i2cBus);
    // Address
    portableMasterWriteI2C(i2cBus, address);
    WaitI2C(i2cBus);

    int count = getBufferElementsCount(buffer);
    int i;
    for (i = 0; i < count; i++) {
        char c = bufferReadChar(buffer);
        portableMasterWriteI2C(i2cBus, c);
        WaitI2C(i2cBus);
    }

    portableStopI2C(i2cBus);
}

void i2cMasterWriteChar(I2cBus* i2cBus, unsigned char address, unsigned char c) {
    // We append to a buffer
    portableStartI2C(i2cBus);
    // Wait till Start sequence is completed
    WaitI2C(i2cBus);

    // Address
    portableMasterWriteI2C(i2cBus, address);
    WaitI2C(i2cBus);

    // Data
    portableMasterWriteI2C(i2cBus, c);
    WaitI2C(i2cBus);

    portableStopI2C(i2cBus);
    WaitI2C(i2cBus);
}

unsigned char i2cMasterReadChar(I2cBus* i2cBus, unsigned char address) {
    portableStartI2C(i2cBus);
    WaitI2C(i2cBus);

    // send the address again with read bit
    portableMasterWriteI2C(i2cBus, address | 0x01);
    WaitI2C(i2cBus);

    unsigned char data = portableMasterReadI2C(i2cBus);
    WaitI2C(i2cBus);

    portableStopI2C(i2cBus);
    WaitI2C(i2cBus);
    return data;
}

unsigned char i2cMasterReadRegisterValue(I2cBus* i2cBus, unsigned char address, unsigned char commandRegister) {
    // Set the register command
    WaitI2C(i2cBus);
    portableStartI2C(i2cBus);

    WaitI2C(i2cBus);
    portableMasterWaitSendI2C(i2cBus);

    WaitI2C(i2cBus);
    // send the address
    portableMasterWriteI2C(i2cBus, address);

    WaitI2C(i2cBus);
    // send the register
    portableMasterWriteI2C(i2cBus, commandRegister);

    WaitI2C(i2cBus);
    portableStopI2C(i2cBus);

    WaitI2C(i2cBus);
    // Read the register command
    portableStartI2C(i2cBus);

    WaitI2C(i2cBus);
    portableMasterWaitSendI2C(i2cBus);
    // send the address again with read bit
    portableMasterWriteI2C(i2cBus, address | 0x01);
    WaitI2C(i2cBus);
    // read the data
    char data = portableMasterReadI2C(i2cBus);
    portableStopI2C(i2cBus);
    return data;
}

void i2cMasterRegisterReadBuffer(I2cBus* i2cBus, unsigned char address, unsigned char reg, unsigned char length, Buffer* buffer){
    // Set the register command
    i2cMasterWriteChar(i2cBus, address, reg);

    // read the data
    portableStartI2C(i2cBus);
    WaitI2C(i2cBus);

    portableMasterWriteI2C(i2cBus, address | 0x01);

    int i;
    for (i = 0; i <(length-1) ; i++) {
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

void i2cMasterReadBuffer(I2cBus* i2cBus, unsigned char address, unsigned char length, Buffer* buffer){
    portableStartI2C(i2cBus);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBus, address);

    // read the data
    portableStartI2C(i2cBus);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBus, address | 0x01);

    int i;
    for (i = 0; i <length ; i++) {
        char c = portableMasterReadI2C(i2cBus);
        portableAckI2C(i2cBus);
        WaitI2C(i2cBus);
        bufferWriteChar(buffer, c);
    }
    portableStopI2C(i2cBus);
    WaitI2C(i2cBus);
}

