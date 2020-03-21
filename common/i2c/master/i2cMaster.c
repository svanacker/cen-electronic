#include "i2cMaster.h"
#include "../i2cCommon.h"

#include "../../../common/error/error.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/i2c/i2cCommon.h"
#include "../../../common/io/buffer.h"

void i2cMasterWriteBuffer(I2cBusConnection* i2cBusConnection, Buffer* buffer) {
    if (i2cBusConnection->error != ERROR_NONE) {
        return;
    }
    portableMasterWaitSendI2C(i2cBusConnection);
    // Wait till Start sequence is completed
    WaitI2cBusConnection(i2cBusConnection);

    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    // Address
    unsigned char address = i2cBusConnection->i2cAddress;
    portableMasterWriteI2C(i2cBusConnection, address);
    WaitI2cBusConnection(i2cBusConnection);

    int count = getBufferElementsCount(buffer);
    int i;
    for (i = 0; i < count; i++) {
        unsigned char c = bufferReadChar(buffer);
        portableMasterWriteI2C(i2cBusConnection, c);
        WaitI2cBusConnection(i2cBusConnection);
    }

    portableMasterStopI2C(i2cBusConnection);
}

void i2cMasterWriteChar(I2cBusConnection* i2cBusConnection, unsigned char address, unsigned char c) {
    if (i2cBusConnection->error != ERROR_NONE) {
        return;
    }
    // We append to a buffer
    portableMasterStartI2C(i2cBusConnection);
    // Wait till Start sequence is completed
    WaitI2cBusConnection(i2cBusConnection);

    // Address
    portableMasterWriteI2C(i2cBusConnection, address);
    WaitI2cBusConnection(i2cBusConnection);

    // Data
    portableMasterWriteI2C(i2cBusConnection, c);
    WaitI2cBusConnection(i2cBusConnection);

    portableMasterStopI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
}

unsigned char i2cMasterReadChar(I2cBusConnection* i2cBusConnection) {
    if (i2cBusConnection->error != ERROR_NONE) {
        return 0x00;
    }
    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);

    // send the address again with read bit
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress | 0x01);
    WaitI2cBusConnection(i2cBusConnection);

    unsigned char data = portableMasterReadI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);

    portableMasterStopI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    return data;
}

unsigned char i2cMasterReadRegisterValue(I2cBusConnection* i2cBusConnection, unsigned char commandRegister) {
    if (i2cBusConnection->error != ERROR_NONE) {
        return 0x00;
    }
    unsigned char address = i2cBusConnection->i2cAddress;

    // Set the register command
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterStartI2C(i2cBusConnection);

    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWaitSendI2C(i2cBusConnection);

    WaitI2cBusConnection(i2cBusConnection);
    // send the address
    portableMasterWriteI2C(i2cBusConnection, i2cBusConnection->i2cAddress);

    WaitI2cBusConnection(i2cBusConnection);
    // send the register
    portableMasterWriteI2C(i2cBusConnection, commandRegister);

    WaitI2cBusConnection(i2cBusConnection);
    portableMasterStopI2C(i2cBusConnection);

    WaitI2cBusConnection(i2cBusConnection);
    // Read the register command
    portableMasterStartI2C(i2cBusConnection);

    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWaitSendI2C(i2cBusConnection);
    // send the address again with read bit
    portableMasterWriteI2C(i2cBusConnection, address | 0x01);
    WaitI2cBusConnection(i2cBusConnection);
    // read the data
    unsigned char data = portableMasterReadI2C(i2cBusConnection);
    portableMasterStopI2C(i2cBusConnection);
    return data;
}

void i2cMasterRegisterReadBuffer(I2cBusConnection* i2cBusConnection, unsigned char reg, unsigned int length, Buffer* buffer) {
    if (i2cBusConnection->error != ERROR_NONE) {
        return;
    }
    unsigned char address = i2cBusConnection->i2cAddress;
    // Set the register command
    i2cMasterWriteChar(i2cBusConnection, address, reg);

    // read the data
    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);

    portableMasterWriteI2C(i2cBusConnection, address | 0x01);

    unsigned int i;
    for (i = 0; i < (length - 1); i++) {
        unsigned char c = portableMasterReadI2C(i2cBusConnection);
        portableMasterAckI2C(i2cBusConnection);
        WaitI2cBusConnection(i2cBusConnection);
        bufferWriteChar(buffer, c);
    }
    unsigned char c = portableMasterReadI2C(i2cBusConnection);
    portableMasterNackI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    bufferWriteChar(buffer, c);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
}

void i2cMasterReadBuffer(I2cBusConnection* i2cBusConnection, unsigned int length, Buffer* buffer) {
    if (i2cBusConnection->error != ERROR_NONE) {
        return;
    }
    unsigned char address = i2cBusConnection->i2cAddress;

    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, address);

    // read the data
    portableMasterStartI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, address | 0x01);

    unsigned int i;
    for (i = 0; i < length; i++) {
        unsigned char c = portableMasterReadI2C(i2cBusConnection);
        portableMasterAckI2C(i2cBusConnection);
        WaitI2cBusConnection(i2cBusConnection);
        bufferWriteChar(buffer, c);
    }
    portableMasterStopI2C(i2cBusConnection);
    WaitI2cBusConnection(i2cBusConnection);
}

