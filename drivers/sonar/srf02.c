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
unsigned int getSRF02Address(I2cBus* i2cBus, unsigned char sonarIndex) {
    return SRF02_DEFAULT_ADDRESS + sonarIndex * 2;
}

unsigned char readSRF02(I2cBus* i2cBus, char addr, char reg) {
    portableStartI2C(i2cBus);
    portableMasterWaitSendI2C(i2cBus);
    // send the address
    portableMasterWriteI2C(i2cBus, addr);
    WaitI2C(i2cBus);
    // send the register
    portableMasterWriteI2C(i2cBus, reg);
    WaitI2C(i2cBus);
    portableStopI2C(i2cBus);
    WaitI2C(i2cBus);
    portableStartI2C(i2cBus);
    portableMasterWaitSendI2C(i2cBus);
    // send the address again with read bit
    portableMasterWriteI2C(i2cBus, addr + 1);
    WaitI2C(i2cBus);
    // read the data
    unsigned char data = portableMasterReadI2C(i2cBus);
    portableStopI2C(i2cBus);
    return data;
}

void writeSRF02Command(I2cBus* i2cBus, char addr, char reg, char cmd) {
    portableStartI2C(i2cBus);
    // Wait till Start sequence is completed
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBus, addr);
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBus, reg);
    WaitI2C(i2cBus);
    // command
    portableMasterWriteI2C(i2cBus, cmd);
    WaitI2C(i2cBus);
    portableStopI2C(i2cBus);
}

void internalChangeAddressLine(I2cBus* i2cBus, unsigned char oldAddress, unsigned char value) {
  WaitI2C(i2cBus);
  portableStartI2C(i2cBus);
  portableMasterWriteI2C(i2cBus, oldAddress);
  WaitI2C(i2cBus);
  portableMasterWriteI2C(i2cBus, 0);
  WaitI2C(i2cBus);
  portableMasterWriteI2C(i2cBus, value);
  WaitI2C(i2cBus);
  portableStopI2C(i2cBus);
  WaitI2C(i2cBus);
}

void SRF02ChangeAddress(I2cBus* i2cBus, unsigned char oldAddress, unsigned char newAddress) {
  // StartI2C();
  // MasterWriteI2C(addr);
  // command register
  internalChangeAddressLine(i2cBus, oldAddress, CHANGE_ADDRESS_FIRST_COMMAND);
  internalChangeAddressLine(i2cBus, oldAddress, CHANGE_ADDRESS_SECOND_COMMAND);
  internalChangeAddressLine(i2cBus, oldAddress, CHANGE_ADDRESS_THIRD_COMMAND);
  internalChangeAddressLine(i2cBus, oldAddress, newAddress);
  // StopI2C();
}

unsigned int getSRF02SoftwareRevision(I2cBus* i2cBus, unsigned char sonarIndex) {
    unsigned char srf02Address = getSRF02Address(i2cBus, sonarIndex);
    return readSRF02(i2cBus, srf02Address, REGISTER_0);
}

void startSRF02Ranging(I2cBus* i2cBus, unsigned char sonarIndex) {
    unsigned char srf02Address = getSRF02Address(i2cBus, sonarIndex);
    writeSRF02Command(i2cBus, srf02Address, REGISTER_0, CM_RANGE_MODE);
}

unsigned int getSRF02Distance(I2cBus* i2cBus, unsigned char sonarIndex) {
    startSRF02Ranging(i2cBus, sonarIndex);
    delaymSec(100);
    unsigned int result = getSRF02DistanceEndRanging(i2cBus, sonarIndex);
    return result;
}

unsigned int getSRF02DistanceEndRanging(I2cBus* i2cBus, unsigned char sonarIndex) {
    unsigned char srf02Address = getSRF02Address(i2cBus, sonarIndex);
    unsigned char datah = readSRF02(i2cBus, srf02Address, 2);
    unsigned char datal = readSRF02(i2cBus, srf02Address, 3);
    unsigned int data = (datah << 8) + datal;
    return (data);
}
