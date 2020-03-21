#ifndef MOTION_DEVICE_H
#define MOTION_DEVICE_H

#include <stdbool.h>

#include "../../../common/eeprom/eeprom.h"
#include "../../../common/io/outputStream.h"

#include "../../../device/deviceDescriptor.h"

#include "../../../motion/pid/pidMotion.h"

/**
 * Returns a descriptor around motion.
 * @param eeprom_ the eeprom to load the default speed and acceleration values
 * @param pidMotionParam the pidMotion object with all instructions and pid parameters
 * @param loadDefaultValues if we load the default values into the eeprom (useful for pc simulation)
 * @return a descriptor for motion device
 */
DeviceDescriptor* getMotionDeviceDescriptor(PidMotion* pidMotionParam);

/**
 * Notify the main Board that the motorBoard has reached the asked position.
 * @param outputStream the outputStream to notify the main Board
 * MrXXXXXX-YYYYYY-AAAA
 * XXXX for the position along Y Axis in mm
 * YYYY for the position along Y Axis in mm
 * AAAA for the position in 1/10 deg
 * @param notificationOutputStream the outputStream to notify the main Board
 */
void notifyReached(OutputStream* notificationOutputStream);

/**
 * Notify the main Board that the motorBoard has failed to reach the asked position
 * It sends a message like this
 * MSXXXXXX-YYYYYY-AAAA
 * XXXXXX for the position along Y Axis in mm
 * YYYYYY for the position along Y Axis in mm
 * AAAA for the position in 1/10 deg
 * @param notificationOutputStream the outputStream to notify the main Board
 */
void notifyShocked(OutputStream* notificationOutputStream);

/**
 * Notify the main Board that the motorBoard has failed to reach the asked position
 * It sends a message like this
 * MkXXXXXX-YYYYYY-AAAA
 * XXXXXX for the position along Y Axis in mm
 * YYYYYY for the position along Y Axis in mm
 * AAAA for the position in 1/10 deg
 * @param notificationOutputStream the outputStream to notify the main Board
 */
void notifyBlocked(OutputStream* notificationOutputStream);

/**
 * Notify the main Board that the motorBoard is moving.
 * It sends a message like this
 * MmXXXXXX-YYYYYY-AAAA
 * XXXXXX for the position along Y Axis in mm
 * YYYYYY for the position along Y Axis in mm
 * AAAA for the position in 1/10 deg
 * @param outputStream the outputStream to notify the main Board
 */
void notifyMoving(OutputStream* outputStream);

/**
 * Notify the main Board that the motorBoard has stopped because a board has set that there is an obstable.
 * It sends a message like this
 * MoXXXXXX-YYYYYY-AAAA
 * XXXXXX for the position along Y Axis in mm
 * YYYYYY for the position along Y Axis in mm
 * AAAA for the position in 1/10 deg
 * @param notificationOutputStream the outputStream to notify the main Board
 */
void notifyObstacle(OutputStream* notificationOutputStream);

/**
 * Notify the main Board that the motorBoard has stopped because a board has 
 * set that it does not reach the position before a timeout.
 * It sends a message like this
 * MoXXXXXX-YYYYYY-AAAA
 * XXXXXX for the position along Y Axis in mm
 * YYYYYY for the position along Y Axis in mm
 * AAAA for the position in 1/10 deg
 * @param notificationOutputStream the outputStream to notify the main Board
 */
void notifyFailed(OutputStream* notificationOutputStream);

#endif

