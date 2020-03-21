#ifndef TOMATOE_H
#define TOMATOE_H

#include "../../device/device.h"

/** Define the index of the relay. */
#define TOMATOE_RELAY_INDEX 0x01

/**
 * Enable or disable the tomatoe engine.
 */
void setTomatoeEnabled(int value);

/**
 * Get the descriptor on tomatoe Engine.
 */
DeviceDescriptor getTomatoe2010DeviceDescriptor();

#endif
