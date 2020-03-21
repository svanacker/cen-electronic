#ifndef ROBOT_SONAR_DETECTOR_DEVICE_INTERFACE_H
#define ROBOT_SONAR_DETECTOR_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

#define COMMAND_SET_SONAR_STATUS            '<'

/**
 * Get the robotSonarDetector interface.
 */
DeviceInterface* getRobotSonarDetectorDeviceInterface();

#endif
