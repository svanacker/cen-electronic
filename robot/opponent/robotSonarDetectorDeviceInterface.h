#ifndef ROBOT_SONAR_DETECTOR_DEVICE_INTERFACE_H
#define ROBOT_SONAR_DETECTOR_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

#define ROBOT_SONAR_DETECTOR_DEVICE_HEADER  '#'

#define COMMAND_SET_SONAR_STATUS            '<'

/**
* Get the robotSonarDetector interface.
*/
DeviceInterface* getRobotSonarDetectorDeviceInterface();

#endif
