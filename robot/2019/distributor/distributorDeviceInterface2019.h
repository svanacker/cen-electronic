#ifndef DISTRIBUTOR_DEVICE_INTERFACE_2019_H
#define DISTRIBUTOR_DEVICE_INTERFACE_2019_H

#include "../../../device/device.h"
#include "../../../device/deviceConstants.h"

// PREPARE TAKE
#define COMMAND_2019_DISTRIBUTOR_PREPARE_TAKE                    't'

// TAKE
#define COMMAND_2019_DISTRIBUTOR_TAKE                            'T'

// ACCELERATOR PREPARATOR DROP
#define COMMAND_2019_DISTRIBUTOR_ACCELERATOR_FAKE_INIT           'i'

#define COMMAND_2019_DISTRIBUTOR_ACCELERATOR_PREPARE_DROP        'd'


// ACCELERATOR DROP
#define COMMAND_2019_DISTRIBUTOR_ACCELERATOR_DROP                'D'

/**
 * Get the device interface for Distributor 2019.
 */
DeviceInterface* getDistributor2019DeviceInterface(void);

#endif
