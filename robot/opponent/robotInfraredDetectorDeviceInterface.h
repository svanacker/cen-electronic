#ifndef ROBOT_INFRARED_DETECTOR_DEVICE_INTERFACE_H
#define ROBOT_INFRARED_DETECTOR_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Ask the status of the infrared detection. */
#define COMMAND_INFRARED_DETECTOR_DETECTION         'X'

#define DETECTOR_FORWARD_INDEX            0
#define DETECTOR_BACKWARD_INDEX            1

/** When detector detection is notified. */
#define NOTIFY_INFRARED_DETECTOR_DETECTION         'O'

/**
* Interface for Robot Infrared Detector Device
*/
DeviceInterface* getRobotInfraredDetectorDeviceInterface();

#endif

