#ifndef COMMON_BEACON_DEVICE_INTERFACE_H
#define COMMON_BEACON_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Redirect commands to Jennic. */
#define COMMAND_REDIRECT_TO_JENNIC             '@'

/** Light on/off the local Jennic. */
#define COMMAND_LOCAL_LIGHT                    'l'

/** Send a RST to Jennic. */
#define COMMAND_RESET_JENNIC                'c'

/** Show In Data (real Data, not ack or command response from Jennic). */
#define COMMAND_SHOW_DATA_FROM_JENNIC         'S'


// Common definition, but the implementation of device is specific

/** Run the servos for the laser. */
#define COMMAND_BEACON_SERVO_RUN            'r'

/** Stop the servos for the laser. */
#define COMMAND_BEACON_SERVO_STOP            's'

/** Run the servos for the laser. */
#define COMMAND_REMOTE_BEACON_SERVO_RUN            COMMAND_BEACON_SERVO_RUN

/** Stop the servos for the laser. */
#define COMMAND_REMOTE_BEACON_SERVO_STOP        COMMAND_BEACON_SERVO_STOP


/**
 * Interface for Device
 */
DeviceInterface* getCommonBeaconDeviceInterface();

#endif

