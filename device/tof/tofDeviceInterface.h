#ifndef TOF_DEVICE_INTERFACE_H
#define TOF_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Command header to do activate the beep . */
#define COMMAND_TOF_BEEP_ON            'B'

/** Command header to do disabled the beep associated to the tof. */
#define COMMAND_TOF_BEEP_OFF           'b'

/** Command to test a tof or all tofs after a collision */
#define COMMAND_TOF_SEARCH_IF_COLLIDING 'c'

/** Command header to get the sonar value. */
#define COMMAND_TOF_GET_DISTANCE      'r'

/** Command header to debug the configuration (excluding network) of all tofs */
#define COMMAND_TOF_LIST_CONFIG       'C'

/** Command header to debug the network of all tofs */
#define COMMAND_TOF_LIST_NETWORK      'N'

/** Command header to debug the detection values of all tofs */
#define COMMAND_TOF_LIST_DETECTED     'D'

/** Command header to launch a tracker system with a notification system */
#define COMMAND_TOF_TRACK             't'

/** Command header to reset & restart a specific Tof */
#define COMMAND_TOF_RESTART           'R'

/**
* Interface for Device "Time of Flight".
*/
DeviceInterface* getTofDeviceInterface();

#endif
