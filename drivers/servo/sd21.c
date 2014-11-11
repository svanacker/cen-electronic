#include <i2c.h>

#include "sd21.h"

#include "../device.h"

/** Address to write value. */
#define SD21_ADDRESS_WRITE 0xC2

/** Address to read value. */
#define SD21_ADDRESS_READ 0xC3

/** The register to read the software revision. */
#define REGISTER_SOFTWARE_REVISION 64

/** The register to read the voltage. */
#define REGISTER_VOLTAGE 65

/** The factor to multiply to get the battery voltage value. */
#define BATTERY_MULTIPLY_FACTOR 39

unsigned int getSD21SoftwareRevision(void) {
  unsigned int version;
  IdleI2C();
  StartI2C();
  /* Wait till Start sequence is completed */
  while(I2CCONbits.SEN);
  MasterWriteI2C(SD21_ADDRESS_WRITE);
  IdleI2C();
  MasterWriteI2C(REGISTER_SOFTWARE_REVISION);
  IdleI2C();  
  StopI2C();

  IdleI2C();
  StartI2C();
  /* Wait till Start sequence is completed */
  while(I2CCONbits.SEN)
  //adddresse I2C de la carte
  MasterWriteI2C(SD21_ADDRESS_READ);
  IdleI2C();
  version = MasterReadI2C();
  IdleI2C();
  StopI2C();
  return (version);
}

char getSD21BatteryLevel (void) {
  unsigned char result;
 
  IdleI2C();
  StartI2C();
  /* Wait till Start sequence is completed */
  while(I2CCONbits.SEN);
  MasterWriteI2C(SD21_ADDRESS_WRITE);
  IdleI2C();
  MasterWriteI2C(REGISTER_VOLTAGE);
  IdleI2C();
  StopI2C();
  IdleI2C();

  StartI2C();
  /* Wait till Start sequence is completed */
  while(I2CCONbits.SEN)
  MasterWriteI2C(SD21_ADDRESS_READ);
  IdleI2C();
  result = MasterReadI2C();// * BATTERY_MULTIPLY_FACTOR;
  IdleI2C();

  return result;
}

void commandSD21(char servo, char speed, int position) {
  char dataHigh = position >> 8;
  char dataLow = position & 0xFF;
  IdleI2C();
  StartI2C();
  /* Wait till Start sequence is completed */
  while(I2CCONbits.SEN);
  MasterWriteI2C(SD21_ADDRESS_WRITE);
  IdleI2C();
  MasterWriteI2C((servo-1) * 3);
  IdleI2C();
  MasterWriteI2C(speed);        
  IdleI2C();
  MasterWriteI2C(dataLow);        
  IdleI2C();
  MasterWriteI2C(dataHigh);        
  IdleI2C();

  StopI2C();
}

// Device Interface

void initSD21(void) {
    getSD21SoftwareRevision();
    getSD21BatteryLevel();
}

void stopSD21(void) {
    // We can not know the value of stop for every servo, so we don't do anything.
}

const char* getSD21DeviceName( void ) {
    return "SD21";
}

unsigned int isSD21DeviceOk() {
    return getSD21SoftwareRevision() < 255;
}

DeviceDescriptor getSD21DeviceDescriptor() {
    DeviceDescriptor result;
    result.deviceInit = &initSD21;
    result.deviceShutDown = &stopSD21;
    result.deviceIsOk = &isSD21DeviceOk;
    result.deviceGetSoftwareRevision = &getSD21SoftwareRevision;
    result.deviceGetName = &getSD21DeviceName;
    result.enabled = 1;

    return result;
}
