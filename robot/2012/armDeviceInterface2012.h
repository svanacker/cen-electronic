#ifndef ARM_DEVICE_INTERFACE_2012_H
#define ARM_DEVICE_INTERFACE_2012_H

#include "../../device/device.h"
#include "../../device/deviceConstants.h"

/**
 * Up the arm 2012.
 */
#define COMMAND_ARM_2012_UP            'I'

/**
 * Down the arm 2012.
 */
#define COMMAND_ARM_2012_DOWN        'J'

/**
 * Index of Left Arm.
 */
#define ARM_LEFT                      0x01

/**
 * Index of Right Arm
 */
#define ARM_RIGHT                     0x02

/**
 * Get the device interface for arm 2012.
 */
DeviceInterface* getArm2012DeviceInterface();

#endif
