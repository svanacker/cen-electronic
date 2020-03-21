#ifndef RLY08_H
#define RLY08_H

#include "relay.h"
#include "../../common/i2c/i2cBusConnectionList.h"

#define ALL_RELAY_ON 100
#define RELAY_1_ON 101
#define RELAY_2_ON 102
#define RELAY_3_ON 103
#define RELAY_4_ON 104
#define RELAY_5_ON 105
#define RELAY_6_ON 106
#define RELAY_7_ON 107
#define RELAY_8_ON 108

#define ALL_RELAY_OFF 110
#define RELAY_1_OFF 111
#define RELAY_2_OFF 112
#define RELAY_3_OFF 113
#define RELAY_4_OFF 114
#define RELAY_5_OFF 115
#define RELAY_6_OFF 116
#define RELAY_7_OFF 117
#define RELAY_8_OFF 118

/** The register which contains the software revision */
#define RLY08_REGISTER_SOFTWARE_REVISION 0

/** The register which enables to send command */
#define RLY08_REGISTER_COMMAND 0

/** The register which contains the state of the relay */
#define RLY08_REGISTER_RELAY_STATES 1

// First sequence command used to change I2C addres
#define RLY08_CHANGE_ADDRESS_FIRST_COMMAND 0xA0

// Second sequence command used to change I2C addres
#define RLY08_CHANGE_ADDRESS_SECOND_COMMAND 0xAA

// Third sequence command used to change I2C addres
#define RLY08_CHANGE_ADDRESS_THIRD_COMMAND 0xA5

/** The default address of the RLY08 */
#define RLY08_DEFAULT_ADDRESS 0x70

/** The name of the Device */
#define RLY08_DEVICE_NAME "RLY08"

/** How many relay on the RLY08. */
#define RLY08_RELAY_COUNT  8

/**
 * Initialize the driver.
 */
void initRLY08(I2cBusConnection* i2cBusConnection);

/**
 * Check if the device is OK
 *
 * @return True if device is OK
 */
bool isRLY08DeviceOk(I2cBusConnection* i2cBusConnection);

// char[] getDeviceName();

/**
 * Change the states of the all 8 relays
 * @param relayStates the word to change relay states
 * the value must be in binary : 1 = active, 0 = inactive
 * Ex : 1111 1111 = Alls ons, 0000 0000 = Alls Off
 * 0000 0010 = Only relay 02 ON
 */
void setRelayStates(I2cBusConnection* i2cBusConnection, unsigned int relayStates);

/**
 * Change the state of one relay
 * @param relay the index of the relay between 1 and 8
 * @param value true if the relay must be on, false to be off
 */
void setRelayState(I2cBusConnection* i2cBusConnection, unsigned int relay, unsigned int value);

/**
 * Send a command to the RLY08 Board
 * @param command the command to send
 */
void sendRLY08Command(I2cBusConnection* i2cBusConnection, int command);

/**
 * The function is BUGGED !!!!
 * Gets the states of the relay
 * @return a value between 0 and 255 which corresponds to a binary value
 * Ex : 1111 1111 = Alls ons, 0000 0000 = Alls Off
 * 0000 0010 = Only relay 02 ON
 */
int getRelayStates(I2cBusConnection* i2cBusConnection);

/**
 * Change the address to a new address
 * @param addr Device address which can be the base following addresses
 * 0x70, 0x72, 0x74, 0x76, 0x78, 0x7A, 0x7C, 0x7E
 */
void changeRLY08Address(I2cBusConnection* i2cBusConnection, int newAddress);

/**
 * Gets the software revision of the software in the RLY08
 */
unsigned int getRLY08SoftwareRevision(I2cBusConnection* i2cBusConnection);

/**
 * Initializes the relay object to drive the RLY08 from Devantech.
 */
void initRelayRLY08(Relay* relay, I2cBusConnection* i2cBusConnection);

#endif
