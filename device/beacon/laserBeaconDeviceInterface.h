#ifndef LASER_BEACON_DEVICE_INTERFACE_H
#define LASER_BEACON_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

// COMMAND INTERFACE

/** Get the position of the detected object. */
#define COMMAND_BEACON_POSITION 'b'

/** Do the operation of calibration on the third beacon which is for the calibration temporary the opponent beacon robot. */
#define COMMAND_BEACON_CALIBRATION 'c'

/** Define beacon configuration. */
#define COMMAND_BEACON_SET_CONFIGURATION 'd'

/** Get information about beacon configuration . */
#define COMMAND_BEACON_CONFIGURATION 'i'

/** Init the Jennic as coordinater. */
#define COMMAND_INIT_JENNIC_AS_COORDINATER		'j'

/** Send hello from the coordinater to router. */
#define COMMAND_SEND_ROBOT_POSITION_FROM_COORDINATER_TO_ROUTER 'h'

/** Redirect command to Jennic. */
#define COMMAND_REDIRECT_TO_JENNIC '@'

/** Light of the jennic on. */
#define COMMAND_ROUTER_LIGHT_ON		    'n'

/** Light of the jennic off. */
#define COMMAND_ROUTER_LIGHT_OFF		'o'

DeviceInterface* getLaserBeaconDeviceInterface();

#endif
