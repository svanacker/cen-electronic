#ifndef ARM_DEVICE_INTERFACE_2019_H
#define ARM_DEVICE_INTERFACE_2019_H

#include "../../../device/device.h"
#include "../../../device/deviceConstants.h"

// LATERAL ARM ---

// ARM CENTER
#define COMMAND_2020_ARM_CENTER                  '|'

// ARM LEFT
#define COMMAND_2020_ARM_LEFT                    '<'

// ARM RIGHT
#define COMMAND_2020_ARM_RIGHT                   '>'

// FLAG ---

// FLAG DOWN
#define COMMAND_2020_FLAG_DOWN                   '_'

// FLAG UP
#define COMMAND_2020_FLAG_UP                     '^'

// HOOK ---

// HOOK DOWN
#define COMMAND_2020_HOOK_DOWN                   'd'
#define COMMAND_2020_HOOK_ALL_DOWN               'D'

// HOOK UP
#define COMMAND_2020_HOOK_UP                     'u'
#define COMMAND_2020_HOOK_ALL_UP                 'U'

// HOOK TAKE
#define COMMAND_2020_HOOK_TAKE                   't'
#define COMMAND_2020_HOOK_ALL_TAKE               'T'

// HOOK RELEASE
#define COMMAND_2020_HOOK_RELEASE                'r'
#define COMMAND_2020_HOOK_ALL_RELEASE            'R'

// HOOK -> COMPLEX

// HOOK PREPARE 
#define COMMAND_2020_HOOK_PREPARE                'p'
#define COMMAND_2020_HOOK_ALL_PREPARE            'P'

// HOOK TAKE AND UP
#define COMMAND_2020_HOOK_TAKE_AND_UP            'k'
#define COMMAND_2020_HOOK_ALL_TAKE_AND_UP        'K'

// HOOK RELEASE
#define COMMAND_2020_HOOK_DOWN_AND_RELEASE       'w'
#define COMMAND_2020_HOOK_ALL_DOWN_AND_RELEASE   'W'

// PREPARE, FORWARD, TAKE, BACK, RELEASE, BACK
#define COMMAND_2020_HOOK_ALL_SEQUENCE           'S'

/**
 * Get the device interface for Arm 2020.
 */
DeviceInterface* getArm2020DeviceInterface(void);

#endif
