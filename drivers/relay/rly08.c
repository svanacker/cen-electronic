#include "relay.h"

#include "../../common/i2c/i2cBusList.h"
#include "../../common/i2c/i2cBusConnectionList.h"

#include "../../common/i2c/master/i2cMaster.h"

#include "rly08.h"

// address for RLY08 (read)
#define readAddr RLY08_DEFAULT_ADDRESS + 1

// address for RLY08 (write)
#define writeAddr RLY08_DEFAULT_ADDRESS

void setRelayStates(I2cBusConnection* i2cBusConnection, unsigned int relayStates) {
    I2cBus* bus = i2cBusConnection->i2cBus;
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(bus);
    portableMasterWriteI2C(i2cBusConnection, writeAddr);
    WaitI2C(bus);
    // send the register
    portableMasterWriteI2C(i2cBusConnection, RLY08_REGISTER_RELAY_STATES);
    WaitI2C(bus);
    // send the value
    portableMasterWriteI2C(i2cBusConnection, relayStates);
    WaitI2C(bus);
    portableMasterStopI2C(i2cBusConnection);
}

  void setRelayState(I2cBusConnection* i2cBusConnection, unsigned int relay, unsigned int value) {
    if (value)
      sendRLY08Command(i2cBusConnection, RELAY_1_ON - 1 + relay);
    else
      sendRLY08Command(i2cBusConnection, RELAY_1_OFF - 1 + relay);
  }


void sendRLY08Command(I2cBusConnection* i2cBusConnection, int command) {
    I2cBus* bus = i2cBusConnection->i2cBus;
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(bus);
    portableMasterWriteI2C(i2cBusConnection, writeAddr);
    WaitI2C(bus);
    // send the register
    portableMasterWriteI2C(i2cBusConnection, RLY08_REGISTER_COMMAND);
    WaitI2C(bus);
    // send the value
    portableMasterWriteI2C(i2cBusConnection, command);
    WaitI2C(bus);
    portableMasterStopI2C(i2cBusConnection);
}

int getRelayStates(I2cBusConnection* i2cBusConnection) {
    I2cBus* bus = i2cBusConnection->i2cBus;
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(bus);
    portableMasterWriteI2C(i2cBusConnection, writeAddr);
    WaitI2C(bus);
    // send the register
    portableMasterWriteI2C(i2cBusConnection, RLY08_REGISTER_RELAY_STATES);
    WaitI2C(bus);

    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(bus);
    // send the address again with read bit
    portableMasterWriteI2C(i2cBusConnection, readAddr);
    WaitI2C(bus);
    // send the register
    portableMasterWriteI2C(i2cBusConnection, RLY08_REGISTER_RELAY_STATES);
    // read the data - and send an ACK
    int data = portableMasterReadI2C(i2cBusConnection);
    portableMasterStopI2C(i2cBusConnection);
    return(data);
}

void changeRLY08Address(I2cBusConnection* i2cBusConnection, int newAddress) {
    I2cBus* bus = i2cBusConnection->i2cBus;
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(bus);
    portableMasterWriteI2C(i2cBusConnection, writeAddr);
    WaitI2C(bus);
    // command register
    portableMasterWriteI2C(i2cBusConnection, RLY08_REGISTER_COMMAND);
    WaitI2C(bus);

    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(bus);
    portableMasterWriteI2C(i2cBusConnection, RLY08_CHANGE_ADDRESS_FIRST_COMMAND);
    WaitI2C(bus);
    portableMasterWriteI2C(i2cBusConnection, RLY08_CHANGE_ADDRESS_SECOND_COMMAND);
    WaitI2C(bus);
    portableMasterWriteI2C(i2cBusConnection, RLY08_CHANGE_ADDRESS_THIRD_COMMAND);
    portableMasterWriteI2C(i2cBusConnection, newAddress);
    portableMasterStopI2C(i2cBusConnection);
}

  /**
  * Gets the software revision of the software in the RLY08
  */
unsigned int getRLY08SoftwareRevision(I2cBusConnection* i2cBusConnection) {
    I2cBus* bus = i2cBusConnection->i2cBus;
    portableMasterStartI2C(i2cBusConnection);
    
    WaitI2C(bus);
    portableMasterWriteI2C(i2cBusConnection, writeAddr);
    WaitI2C(bus);
    // send the register
    portableMasterWriteI2C(i2cBusConnection, RLY08_REGISTER_SOFTWARE_REVISION);
    WaitI2C(bus);
    
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(bus);
    // send the address again with read bit
    portableMasterWriteI2C(i2cBusConnection, readAddr);
    WaitI2C(bus);
    // read the data
    unsigned char data = portableMasterReadI2C(i2cBusConnection);
    WaitI2C(bus);
    portableMasterStopI2C(i2cBusConnection);
    return data;
}

// DEVICE INTERFACE

I2cBusConnection* getRLY08I2cBusConnection(Relay* relay) {
    return (I2cBusConnection*) (relay->object);
}

void initRLY08(I2cBusConnection* i2cBusConnection) {
    // We need to send command to initialize the relay, but it does not taken
    getRLY08SoftwareRevision(i2cBusConnection);
    sendRLY08Command(i2cBusConnection, ALL_RELAY_ON);
}

void stopRLY08(I2cBusConnection* i2cBusConnection) {
    sendRLY08Command(i2cBusConnection, ALL_RELAY_OFF);
}

bool isRLY08DeviceOk(I2cBusConnection* i2cBusConnection) {
    return getRLY08SoftwareRevision(i2cBusConnection) < 255;
}

// RELAY Implementation

bool relayRLY08Init(Relay* relay) {
    I2cBusConnection* i2cBusConnection = getRLY08I2cBusConnection(relay);
    initRLY08(i2cBusConnection);
    return true;
}

bool relayRLY08ReadValue(Relay* relay, unsigned int relayIndex) {
    return true;
}

void relayRLY08WriteValue(Relay* relay, unsigned int relayIndex, bool value) {
    I2cBusConnection* i2cBusConnection = getRLY08I2cBusConnection(relay);
    
    setRelayState(i2cBusConnection, relayIndex, value);
}

void initRelayRLY08(Relay* relay, I2cBusConnection* busConnection) {
    initRelay(relay,
              relayRLY08Init,
              relayRLY08ReadValue,
              relayRLY08WriteValue,
              RLY08_RELAY_COUNT,
            (int*) busConnection);
}