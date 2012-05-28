#include "../../common/commons.h"

#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/master/i2cMaster.h"

#include "srf02.h"

#include "../../common/delay/delay30F.h"

// First sequence command used to change I2C addres
#define CHANGE_ADDRESS_FIRST_COMMAND 0xA0

// Second sequence command used to change I2C addres
#define CHANGE_ADDRESS_SECOND_COMMAND 0xAA

// Third sequence command used to change I2C addres
#define CHANGE_ADDRESS_THIRD_COMMAND 0xA5

/**
 * Address are range of E0 -> E2 -> ... -> F2
 * @param sonarIndex between 0 and 15
 */
unsigned int getSRF02Address(unsigned char sonarIndex) {
	return SRF02_DEFAULT_ADDRESS + sonarIndex * 2;
}

unsigned char readSRF02(char addr, char reg) {
    portableStartI2C();
	portableMasterWaitSendI2C();
    // send the address
    portableMasterWriteI2C(addr);
    WaitI2C();
    // send the register
    portableMasterWriteI2C(reg);
    WaitI2C();
    portableStopI2C();
    WaitI2C();
    portableStartI2C();
	portableMasterWaitSendI2C();
    // send the address again with read bit
    portableMasterWriteI2C(addr + 1);
    WaitI2C();
    // read the data
    unsigned char data = portableMasterReadI2C();
    portableStopI2C();
    return data;
}

void writeSRF02Command(char addr, char reg, char cmd) {
    portableStartI2C();
    // Wait till Start sequence is completed
    WaitI2C();
    portableMasterWriteI2C(addr);
    WaitI2C();
    portableMasterWriteI2C(reg);
    WaitI2C();
    // command
    portableMasterWriteI2C(cmd);
    WaitI2C();
    portableStopI2C();
}

void internalChangeAddressLine(unsigned char oldAddress, unsigned char value) {
  WaitI2C();
  portableStartI2C();
  portableMasterWriteI2C(oldAddress);
  WaitI2C();
  portableMasterWriteI2C(0);
  WaitI2C();
  portableMasterWriteI2C(value);
  WaitI2C();
  portableStopI2C();
  WaitI2C();
}

void SRF02ChangeAddress(unsigned char oldAddress, unsigned char newAddress) {
  // StartI2C();
  // MasterWriteI2C(addr);
  // command register
  internalChangeAddressLine(oldAddress, CHANGE_ADDRESS_FIRST_COMMAND);
  internalChangeAddressLine(oldAddress, CHANGE_ADDRESS_SECOND_COMMAND);
  internalChangeAddressLine(oldAddress, CHANGE_ADDRESS_THIRD_COMMAND);
  internalChangeAddressLine(oldAddress, newAddress);
  // StopI2C();
}

unsigned int getSRF02SoftwareRevision(unsigned char sonarIndex) {
	unsigned char srf02Address = getSRF02Address(sonarIndex);
    return readSRF02(srf02Address, REGISTER_0);
}

void startSRF02Ranging(unsigned char sonarIndex) {
	unsigned char srf02Address = getSRF02Address(sonarIndex);
    writeSRF02Command(srf02Address, REGISTER_0, CM_RANGE_MODE);
}

unsigned int getSRF02Distance(unsigned char sonarIndex) {
    startSRF02Ranging(sonarIndex);
    delaymSec(100);
    unsigned int result = getSRF02DistanceEndRanging(sonarIndex);
    return result;
}

unsigned int getSRF02DistanceEndRanging(unsigned char sonarIndex) {
	unsigned char srf02Address = getSRF02Address(sonarIndex);
    unsigned char datah = readSRF02(srf02Address, 2);
    unsigned char datal = readSRF02(srf02Address, 3);
    unsigned int data = (datah << 8) + datal;
    return (data);
}
