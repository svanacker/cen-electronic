#ifndef ROBOT_INFRARED_DETECTOR_DEVICE_INTERFACE_H
#define ROBOT_INFRARED_DETECTOR_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"


// COMMAND


/** Ask the status of the infrared detection. */
#define COMMAND_INFRARED_DETECTOR_DETECTION         'r'

/**
 * Enable the Infrared Detector notification.
 */
#define DETECTOR_ENABLE_NOTIFICATION_COMMAND        'e'

/**
 * Disable the Infrared Detector notification
 */
#define DETECTOR_DISABLE_NOTIFICATION_COMMAND       'd'



// NOTIFICATION

/** When detector detection is notified. */
#define NOTIFY_INFRARED_DETECTOR_DETECTION          'N'

/**
 * Interface for Robot Infrared Detector Device
 */
DeviceInterface* getRobotInfraredDetectorDeviceInterface();

#endif

