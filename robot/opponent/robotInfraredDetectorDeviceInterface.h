#ifndef ROBOT_INFRARED_DETECTOR_DEVICE_INTERFACE_H
#define ROBOT_INFRARED_DETECTOR_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

#define COMMAND_INFRARED_DETECTOR_DETECTION		 'X'

#define NOTIFY_INFRARED_DETECTOR_DETECTION		 'O'

/**
* Interface for Robot Infrared Detector Device
*/
DeviceInterface* getRobotInfraredDetectorDeviceInterface();

#endif
