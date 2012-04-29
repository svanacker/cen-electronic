#include <i2c.h>

#include "rly08.h"

#include "../device.h"

  // address for RLY08 (read)
  #define readAddr RLY08_DEFAULT_ADDRESS + 1

  // address for RLY08 (write)
  #define writeAddr RLY08_DEFAULT_ADDRESS

  /**
  * Change the states of the all 8 relays
  * @param relayStates the word to change relay states
  * the value must be in binary : 1 = active, 0 = unactive
  * Ex : 1111 1111 = Alls ons, 0000 0000 = Alls Off
  * 0000 0010 = Only relay 02 ON
  */
  void setRelayStates(int relayStates) {
    StartI2C();
	IdleI2C();
	while(I2CCONbits.SEN);
    MasterWriteI2C(writeAddr);
    IdleI2C();
    // send the register
    MasterWriteI2C(RLY08_REGISTER_RELAY_STATES);
    IdleI2C();
    // send the value
    MasterWriteI2C(relayStates);
    IdleI2C();
    StopI2C();
  }

  /**
  * Change the state of one relay
  * @param relay the index of the relay between 1 and 8
  * @param value true if the relay must be on, false to be off
  */
  void setRelayState(int relay, int value) {
    if (value)
      sendRLY08Command(RELAY_1_ON - 1 + relay);
    else
      sendRLY08Command(RELAY_1_OFF - 1 + relay);
  }


  void sendRLY08Command(int command) {
    StartI2C();
    IdleI2C();
    while(I2CCONbits.SEN);
    MasterWriteI2C(writeAddr);
    IdleI2C();
    // send the register
    MasterWriteI2C(RLY08_REGISTER_COMMAND);
    IdleI2C();
    // send the value
    MasterWriteI2C(command);
    IdleI2C();
    StopI2C();
  }

  /**
  * The function is BUGGED !!!!
  * Gets the states of the relay
  * @return a value between 0 and 255 which corresponds to a binary value
  * Ex : 1111 1111 = Alls ons, 0000 0000 = Alls Off
  * 0000 0010 = Only relay 02 ON
  */
  int getRelayStates() {
    StartI2C();
    IdleI2C();
    // send the address
    MasterWriteI2C(writeAddr);
    IdleI2C();
    // send the register
    MasterWriteI2C(RLY08_REGISTER_RELAY_STATES);
    IdleI2C();

    StartI2C();
    // send the address again with read bit
    MasterWriteI2C(readAddr);
    IdleI2C();
    // send the register
    MasterWriteI2C(RLY08_REGISTER_RELAY_STATES);
    // read the data - and send an ACK
    int data = MasterReadI2C();
    StopI2C();
    return(data);
  }

  /**
  * Change the address to a new address
  * @param addr Device address which can be the base following addresses
   * 0x70, 0x72, 0x74, 0x76, 0x78, 0x7A, 0x7C, 0x7E
  */
  void changeRLY08Address(int newAddress) {
    StartI2C();
    IdleI2C();
	while(I2CCONbits.SEN);
    MasterWriteI2C(writeAddr);
    IdleI2C();
    // command register
    MasterWriteI2C(RLY08_REGISTER_COMMAND);
    IdleI2C();

    StartI2C();
	while(I2CCONbits.SEN);
    MasterWriteI2C(RLY08_CHANGE_ADDRESS_FIRST_COMMAND);
    IdleI2C();
    MasterWriteI2C(RLY08_CHANGE_ADDRESS_SECOND_COMMAND);
    IdleI2C();
    MasterWriteI2C(RLY08_CHANGE_ADDRESS_THIRD_COMMAND);
    MasterWriteI2C(newAddress);
    StopI2C();
  }

  /**
  * Gets the software revision of the software in the RLY08
  */
  unsigned int getRLY08SoftwareRevision() {
    IdleI2C();
    StartI2C();
    IdleI2C();
	while(I2CCONbits.SEN);
    // send the address
    MasterWriteI2C(writeAddr);
    IdleI2C();
    // send the register
    MasterWriteI2C(RLY08_REGISTER_SOFTWARE_REVISION);
    IdleI2C();
    StopI2C();

    IdleI2C();
    StartI2C();
    while(I2CCONbits.SEN);
    // send the address again with read bit
    MasterWriteI2C(readAddr);
    IdleI2C();
    // read the data
    unsigned char data = MasterReadI2C();
    IdleI2C();
    StopI2C();
    return data;
  }

// DEVICE INTERFACE

  void initRLY08() {
    // We need to send command to initialize the relay, but it does not taken
	getRLY08SoftwareRevision();
	sendRLY08Command(ALL_RELAY_ON);
  }

  void stopRLY08() {
	sendRLY08Command(ALL_RELAY_OFF);
  }

  unsigned int isRLY08DeviceOk() {
    return getRLY08SoftwareRevision() < 255;
  }

  const char* getRLY08DeviceName() {
    return "RLY08";
  }

  DeviceDescriptor getRLY08DeviceDescriptor() {
	DeviceDescriptor result;
	result.deviceInit = &initRLY08;
	result.deviceShutDown = &stopRLY08;
	result.deviceIsOk = &isRLY08DeviceOk;
	result.deviceGetSoftwareRevision = &getRLY08SoftwareRevision;
	result.deviceGetName = &getRLY08DeviceName;
	result.enabled = 1;

	return result;
  }
