#ifndef RELAY_PC_H
#define RELAY_PC_H

#include "../relay.h"

/** 
 * Init a fake relay Pc so that we could simulate it.
 * @param relay the pointer (simulates POO)
 * @param relayValue pointer on an int value to store the value which is used to store the different read and write
 */
void initRelayPc(Relay* relay, int* pRelayValue);

#endif
