#include <i2c.h>
#include "srf08.h"

// First sequence command used to change I2C addres
#define CHANGE_ADDRESS_FIRST_COMMAND 0xA0

// Second sequence command used to change I2C addres
#define CHANGE_ADDRESS_SECOND_COMMAND 0xAA

// Third sequence command used to change I2C addres
#define CHANGE_ADDRESS_THIRD_COMMAND 0xA5

// Command to get the software revision (read)
#define REGISTER_SOFTWARE_REVISION 0

// Command to write the mode of the SRF08
#define REGISTER_MODE 0

// Command to manage the light
#define REGISTER_LIGHT 1

// Command to manage the distance
#define REGISTER_DISTANCE 2

static int distances[16];

// PRIVATE FUNCTIONS

void internalChangeAddressLine(unsigned char oldAddress, unsigned char value) {
  StartI2C();
  MasterWriteI2C(oldAddress);
  IdleI2C();
  MasterWriteI2C(0);
  IdleI2C();
  MasterWriteI2C(value);
  IdleI2C();
  StopI2C();
}

// PUBLIC FUNCTIONS

void initSRF08(unsigned char addr, unsigned char mode) {
  StartI2C();

  // select the SRF08
  MasterWriteI2C(addr);
  IdleI2C();

  // command register the mode
  MasterWriteI2C(REGISTER_MODE);
  IdleI2C();

  // selected mode (centimeter by example)
  MasterWriteI2C(mode);
  // 65 ms tempo required
  IdleI2C();

  StopI2C();
}

unsigned char getSRF08SoftwareRev(unsigned char addr) {
  unsigned char data = 255;
  while (data == 255) {
    // get the software rev
    StartI2C();

    // send the address of the SRF08
    MasterWriteI2C(addr);
    IdleI2C();

    // send the register to get Software revision
    MasterWriteI2C(REGISTER_SOFTWARE_REVISION);
    IdleI2C();
    StartI2C();

    // send the address again with read bit
    MasterWriteI2C(addr + 1);
    IdleI2C();
    // read the data - and send an ACK
    data = MasterReadI2C();
  }
  StopI2C();
  return data;
}

unsigned char isSRF08DeviceOk(unsigned char addr) {
  return (getSRF08SoftwareRev(addr) < 255);
}

void changeAddress(unsigned char addr, unsigned char oldAddress, unsigned char newAddress) {
  StartI2C();
  MasterWriteI2C(addr);
  // command register
  internalChangeAddressLine(oldAddress, CHANGE_ADDRESS_FIRST_COMMAND);
  internalChangeAddressLine(oldAddress, CHANGE_ADDRESS_SECOND_COMMAND);
  internalChangeAddressLine(oldAddress, CHANGE_ADDRESS_THIRD_COMMAND);
  internalChangeAddressLine(oldAddress, newAddress);
  StopI2C();
}

/**
* Read the distance and returns value depending on the mode which
* was given at the initialisation of the SRF08
*/
unsigned char readDistance(unsigned char addr) {
  StartI2C();

  // select the SRF08
  MasterWriteI2C(addr);
  MasterWriteI2C(REGISTER_DISTANCE);
  StartI2C();
  MasterWriteI2C(addr + 1);

  // Internal register address will increment automatically, so we do not
  // have to restart and select the bus

  int highByte = 0;
  int lowByte = 0;
  int i;
  for (i=0; i<16; i++)
  {
    // TODO : manage the timer and the 255 value if SRF08 not ready
    // high part of int value
    highByte = MasterReadI2C();
    IdleI2C();

    // low part of int value
    if (i == 15)
      lowByte = MasterReadI2C(); // TODO : Normalement, il y a un NAK à demander
    else
      lowByte = MasterReadI2C();

    IdleI2C();
    // System.out.println("h=" + highByte + ";l=" + lowByte);
    // compute the distance
    distances[0] = highByte * 256 + lowByte;
  }
  StopI2C();
  return (distances[0]);
}

