#ifndef BEACON_RECEIVER_INTERFACE_H
#define BEACON_RECEIVER_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/**
* Command header for getting the position of the opponent robot.
*/
#define COMMAND_GET_OPPONENT_ROBOT_POSITION     'o'

/**
 * Command header to set the position of the opponent robot via automatic notification (pull).
 */
#define COMMAND_SET_OPPONENT_ROBOT_POSITION_FROM_LASER_TO_RECEIVER 'w'


#define COMMAND_GET_OPPONENT_ROBOT_MSG_SIZE 9

/**
 * Returns the status of the jennic network node : 
 * JENNIC_NOT_INITIALIZED
 * JENNIC_WAITING_FOR_NODE
 * JENNIC_LINK_CONNECTED
 */
#define COMMANG_GET_RECEIVER_NETWORK_STATUS                            'n'

/** Initialize the jennic as router. */
#define COMMAND_INIT_JENNIC_AS_ROUTER                                'i'

/**
* Interface for Device
*/
DeviceInterface* getBeaconReceiverDeviceInterface();

#endif

