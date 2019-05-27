#ifndef DISTRIBUTOR_DEVICE_INTERFACE_2019_H
#define DISTRIBUTOR_DEVICE_INTERFACE_2019_H

#include "../../../device/device.h"
#include "../../../device/deviceConstants.h"

// DISTRIBUTOR
#define COMMAND_2019_DISTRIBUTOR_PREPARE_TAKE                    't'

#define COMMAND_2019_DISTRIBUTOR_TAKE                            'T'

// ACCELERATOR
#define COMMAND_2019_DISTRIBUTOR_ACCELERATOR_FAKE_INIT           'i'

#define COMMAND_2019_DISTRIBUTOR_ACCELERATOR_FAKE_MOVE_FORWARD   'm'

#define COMMAND_2019_DISTRIBUTOR_ACCELERATOR_PREPARE_DROP        'd'

#define COMMAND_2019_DISTRIBUTOR_ACCELERATOR_DROP                'D'

#define COMMAND_2019_DISTRIBUTOR_ACCELERATOR_COMPLETE_SEQUENCE   'C'


/**
 * Get the device interface for Distributor 2019.
 */
DeviceInterface* getDistributor2019DeviceInterface(void);

#endif
