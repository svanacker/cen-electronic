#include <i2c.h>

#include "rly08.h"

#include "../device.h"

// address for RLY08 (read)
#define readAddr RLY08_DEFAULT_ADDRESS + 1

// address for RLY08 (write)
#define writeAddr RLY08_DEFAULT_ADDRESS

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
