#include "i2cMaster.h"
#include "../i2cCommon.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/i2c/i2cCommon.h"
#include "../../../common/io/buffer.h"

void i2cMasterWriteBuffer(I2cBusConnection* i2cBusConnection, Buffer* buffer) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    portableMasterWaitSendI2C(i2cBusConnection);
    // Wait till Start sequence is completed
    WaitI2C(i2cBus);

    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    // Address
    unsigned char address = i2cBusConnection->i2cAddress;
    portableMasterWriteI2C(i2cBusConnection, address);
    WaitI2C(i2cBus);

    int count = getBufferElementsCount(buffer);
    int i;
    for (i = 0; i < count; i++) {
        char c = bufferReadChar(buffer);
        portableMasterWriteI2C(i2cBusConnection, c);
        WaitI2C(i2cBus);
    }

    portableMasterStopI2C(i2cBusConnection);
}

void i2cMasterWriteChar(I2cBusConnection* i2cBusConnection, unsigned char address, unsigned char c) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    // We append to a buffer
    portableMasterStartI2C(i2cBusConnection);
    // Wait till Start sequence is completed
    WaitI2C(i2cBus);

    // Address
    portableMasterWriteI2C(i2cBusConnection, address);
    WaitI2C(i2cBus);

    // Data
    portableMasterWriteI2C(i2cBusConnection, c);
    WaitI2C(i2cBus);

    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
}

unsigned char i2cMasterReadChar(I2cBusConnection* i2cBusConnection) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    // send the address again with read bit
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress | 0x01);
    WaitI2C(i2cBus);

    unsigned char data = portableMasterReadI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    return data;
}

unsigned char i2cMasterReadRegisterValue(I2cBusConnection* i2cBusConnection, unsigned char commandRegister) {
    unsigned char address = i2cBusConnection->i2cAddress;
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    // Set the register command
    WaitI2C(i2cBus);
    portableMasterStartI2C(i2cBusConnection);

    WaitI2C(i2cBus);
    portableMasterWaitSendI2C(i2cBusConnection);

    WaitI2C(i2cBus);
    // send the address
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);

    WaitI2C(i2cBus);
    // send the register
    portableMasterWriteI2C(i2cBusConnection, commandRegister);

    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);

    WaitI2C(i2cBus);
    // Read the register command
    portableMasterStartI2C(i2cBusConnection);

    WaitI2C(i2cBus);
    portableMasterWaitSendI2C(i2cBusConnection);
    // send the address again with read bit
    portableMasterWriteI2C(i2cBusConnection, address | 0x01);
    WaitI2C(i2cBus);
    // read the data
    char data = portableMasterReadI2C(i2cBusConnection);
    portableMasterStopI2C(i2cBusConnection);
    return data;
}

void i2cMasterRegisterReadBuffer(I2cBusConnection* i2cBusConnection, unsigned char reg, unsigned char length, Buffer* buffer){
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    unsigned char address = i2cBusConnection->i2cAddress;
    // Set the register command
    i2cMasterWriteChar(i2cBusConnection, address, reg);

    // read the data
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);

    portableMasterWriteI2C(i2cBusConnection, address | 0x01);

    int i;
    for (i = 0; i <(length-1) ; i++) {
        char c = portableMasterReadI2C(i2cBusConnection);
        portableMasterAckI2C(i2cBusConnection);
        WaitI2C(i2cBus);
        bufferWriteChar(buffer, c);
    }
    char c = portableMasterReadI2C(i2cBusConnection);
    portableMasterNackI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    bufferWriteChar(buffer, c);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
}

void i2cMasterReadBuffer(I2cBusConnection* i2cBusConnection, unsigned char length, Buffer* buffer) {
    unsigned char address = i2cBusConnection->i2cAddress;
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, address);

    // read the data
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, address | 0x01);

    int i;
    for (i = 0; i <length ; i++) {
        char c = portableMasterReadI2C(i2cBusConnection);
        portableMasterAckI2C(i2cBusConnection);
        WaitI2C(i2cBus);
        bufferWriteChar(buffer, c);
    }
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
}

