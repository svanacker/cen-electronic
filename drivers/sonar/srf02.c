#include <i2c.h>

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
    StartI2C();
    while (I2CCONbits.SEN);
    // send the address
    MasterWriteI2C(addr);
    IdleI2C();
    // send the register
    MasterWriteI2C(reg);
    IdleI2C();
    StopI2C();
    IdleI2C();
    StartI2C();
    while (I2CCONbits.SEN);
    // send the address again with read bit
    MasterWriteI2C(addr + 1);
    IdleI2C();
    // read the data
    unsigned char data = MasterReadI2C();
    StopI2C();
    return data;
}

void writeSRF02Command(char addr, char reg, char cmd) {
    StartI2C();
    // Wait till Start sequence is completed
    IdleI2C();
    MasterWriteI2C(addr);
    IdleI2C();
    MasterWriteI2C(reg);
    IdleI2C();
    // command
    MasterWriteI2C(cmd);
    IdleI2C();
    StopI2C();
}

void internalChangeAddressLine(unsigned char oldAddress, unsigned char value) {
  IdleI2C();
  StartI2C();
  MasterWriteI2C(oldAddress);
  IdleI2C();
  MasterWriteI2C(0);
  IdleI2C();
  MasterWriteI2C(value);
  IdleI2C();
  StopI2C();
  IdleI2C();
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
