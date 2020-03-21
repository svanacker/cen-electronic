// TODO : Remove Address and use i2cBusConnection->Address

#include "../../common/i2c/i2cCommon.h"

#include "../../common/i2c/master/i2cMaster.h"

#include "srf02.h"

#include "../../common/delay/cenDelay.h"

// First sequence command used to change I2C address
#define CHANGE_ADDRESS_FIRST_COMMAND 0xA0

// Second sequence command used to change I2C address
#define CHANGE_ADDRESS_SECOND_COMMAND 0xAA

// Third sequence command used to change I2C address
#define CHANGE_ADDRESS_THIRD_COMMAND 0xA5

/**
 * Address are range of E0 -> E2 -> ... -> F2
 * @param sonarIndex between 0 and 15
 */
unsigned int getSRF02Address(I2cBusConnection* i2cBusConnection, unsigned char sonarIndex) {
    return SRF02_DEFAULT_ADDRESS + sonarIndex * 2;
}

unsigned char readSRF02(I2cBusConnection* i2cBusConnection, char addr, char reg) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    portableMasterStartI2C(i2cBusConnection);
    portableMasterWaitSendI2C(i2cBusConnection);
    // send the address
    portableMasterWriteI2C(i2cBusConnection, addr);
    WaitI2C(i2cBus);
    // send the register
    portableMasterWriteI2C(i2cBusConnection, reg);
    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterStartI2C(i2cBusConnection);
    portableMasterWaitSendI2C(i2cBusConnection);
    // send the address again with read bit
    portableMasterWriteI2C(i2cBusConnection, addr + 1);
    WaitI2C(i2cBus);
    // read the data
    unsigned char data = portableMasterReadI2C(i2cBusConnection);
    portableMasterStopI2C(i2cBusConnection);
    return data;
}

void writeSRF02Command(I2cBusConnection* i2cBusConnection, char addr, char reg, char cmd) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    portableMasterStartI2C(i2cBusConnection);
    // Wait till Start sequence is completed
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, addr);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, reg);
    WaitI2C(i2cBus);
    // command
    portableMasterWriteI2C(i2cBusConnection, cmd);
    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);
}

void internalChangeAddressLine(I2cBusConnection* i2cBusConnection, unsigned char oldAddress, unsigned char value) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;
    WaitI2C(i2cBus);
    portableMasterStartI2C(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, oldAddress);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, 0);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, value);
    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);
    WaitI2C(i2cBus);
}

void SRF02ChangeAddress(I2cBusConnection* i2cBusConnection, unsigned char oldAddress, unsigned char newAddress) {
    // StartI2C();
    // MasterWriteI2C(addr);
    // command register
    internalChangeAddressLine(i2cBusConnection, oldAddress, CHANGE_ADDRESS_FIRST_COMMAND);
    internalChangeAddressLine(i2cBusConnection, oldAddress, CHANGE_ADDRESS_SECOND_COMMAND);
    internalChangeAddressLine(i2cBusConnection, oldAddress, CHANGE_ADDRESS_THIRD_COMMAND);
    internalChangeAddressLine(i2cBusConnection, oldAddress, newAddress);
    // StopI2C();
}

unsigned int getSRF02SoftwareRevision(I2cBusConnection* i2cBusConnection, unsigned char sonarIndex) {
    unsigned char srf02Address = getSRF02Address(i2cBusConnection, sonarIndex);
    return readSRF02(i2cBusConnection, srf02Address, REGISTER_0);
}

void startSRF02Ranging(I2cBusConnection* i2cBusConnection, unsigned char sonarIndex) {
    unsigned char srf02Address = getSRF02Address(i2cBusConnection, sonarIndex);
    writeSRF02Command(i2cBusConnection, srf02Address, REGISTER_0, CM_RANGE_MODE);
}

unsigned int getSRF02Distance(I2cBusConnection* i2cBusConnection, unsigned char sonarIndex) {
    startSRF02Ranging(i2cBusConnection, sonarIndex);
    delaymSec(100);
    unsigned int result = getSRF02DistanceEndRanging(i2cBusConnection, sonarIndex);
    return result;
}

unsigned int getSRF02DistanceEndRanging(I2cBusConnection* i2cBusConnection, unsigned char sonarIndex) {
    unsigned char srf02Address = getSRF02Address(i2cBusConnection, sonarIndex);
    unsigned char datah = readSRF02(i2cBusConnection, srf02Address, 2);
    unsigned char datal = readSRF02(i2cBusConnection, srf02Address, 3);
    unsigned int data = (datah << 8) + datal;
    return (data);
}
