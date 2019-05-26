#ifndef DISTRIBUTOR_DEVICE_INTERFACE_2019_H
#define DISTRIBUTOR_DEVICE_INTERFACE_2019_H

#include "../../../device/device.h"
#include "../../../device/deviceConstants.h"

// ACCELERATOR DROP
#define COMMAND_2019_DISTRIBUTOR_ACCELERATOR_DROP        'D'

// PREPARE TAKE
#define COMMAND_2019_DISTRIBUTOR_PREPARE_TAKE            'P'

// TAKE
#define COMMAND_2019_DISTRIBUTOR_TAKE                    'T'

/**
 * Get the device interface for Distributor 2019.
 */
DeviceInterface* getDistributor2019DeviceInterface(void);

#endif
