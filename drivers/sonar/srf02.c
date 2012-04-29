#include <i2c.h>

#include "srf02.h"

#include "../../common/delay/delay30F.h"

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

unsigned int getSRF02SoftwareRevision(unsigned char sonar) { //TODO permettre de choisir parmis plusieurs sonar
    return readSRF02(SRF02_DEFAULT_ADDRESS, REGISTER_0);
}

unsigned int getSRF02SoftwareRevisionDeprecated() { //TODO permettre de choisir parmis plusieurs sonar
    return readSRF02(SRF02_DEFAULT_ADDRESS, REGISTER_0);
}

void startSRF02Ranging() {
    writeSRF02Command(SRF02_DEFAULT_ADDRESS, REGISTER_0, CM_RANGE_MODE);
}

unsigned int getSRF02Distance(void) {
    startSRF02Ranging();
    delaymSec(100);
    unsigned int result = getSRF02DistanceEndRanging();
    return result;
}

unsigned int getSRF02DistanceEndRanging() {
    unsigned char datah = readSRF02(SRF02_DEFAULT_ADDRESS, 2);
    unsigned char datal = readSRF02(SRF02_DEFAULT_ADDRESS, 3);
    unsigned int data = (datah << 8) + datal;
    return (data);
}
