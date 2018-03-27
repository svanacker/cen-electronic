#ifndef RELAY_DEBUG_H
#define RELAY_DEBUG_H

#include "relay.h"

#include "../../common/io/outputStream.h"

/**
 * Print a list of states of relay as a table
 */
void printRelayStatesTable(OutputStream* outputStream, Relay* relay);

#endif
