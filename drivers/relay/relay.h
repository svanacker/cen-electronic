#ifndef RELAY_H
#define RELAY_H

#include <stdbool.h>

// forward declaration
struct Relay;
typedef struct Relay Relay;

/**
 * Type of function to initialize the relay.
 */
typedef bool relayInitFunction(Relay* relay);

/**
 * Read if the relay is on or off for the specified relayIndex.
 * @return relayIndex the value of the relay
 */
typedef bool relayReadValueFunction(Relay* relay, unsigned int relayIndex);

/**
 * Write a fake value to replace the switch configuration.
 */
typedef void relayWriteValueFunction(Relay* relay, unsigned int relayIndex, bool value);

/**
 * Defines the contract for switch robot configuration.
 */
struct Relay {
    /** The function which must be used to init the relay */
    relayInitFunction* relayInit;
    /** The function which must be used to read the value of each relay */
    relayReadValueFunction* relayReadValue;
    /** The function which can be used to change the value of a specific relay. */
    relayWriteValueFunction* relayWriteValue;
    /** How many relay are managed .*/
    unsigned int count;
    /** pointer on other object (useful for I2C Connection for example) .*/
    int* object;
};

/** 
 * Init the wrapper around Relay. 
 */
void initRelay(Relay* relay,
        relayInitFunction* relayInit,
        relayReadValueFunction* relayReadValue,
        relayWriteValueFunction* relayWriteValue,
        unsigned int count,
        int* object);

#endif
