#ifndef ROBOT_INFRARED_DETECTOR_DEVICE_H
#define ROBOT_INFRARED_DETECTOR_DEVICE_H

#include "../../device/device.h"
#include "robotInfraredDetector.h"

/**
 * Notify to I2C and UART a detection via Infrared Detector.
 * @param type FORWARD / BACKWARD
 */
void notifyInfraredDetectorDetection(enum InfraredDetectorGroupType type);

/**
 * The descriptor for the robot Infrared Detector device.
 */
DeviceDescriptor* getRobotInfraredDetectorDeviceDescriptor(RobotInfraredDetector* robotDetectorParam);

#endif
