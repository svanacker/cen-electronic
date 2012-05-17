#ifndef ROBOT_INFRARED_DETECTOR_DEVICE_H
#define ROBOT_INFRARED_DETECTOR_DEVICE_H

#include "../../device/device.h"

/**
 * Notify to I2C and UART a detection via Infrared Detector.
 * @param type FORWARD / BACKWARD
 */
void notifyInfraredDetectorDetection(int type);

/**
 * The descriptor for the robot Infrared Detector device.
 */
DeviceDescriptor* getRobotInfraredDetectorDeviceDescriptor();

#endif
