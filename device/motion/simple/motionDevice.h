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
 * kXXXX-YYYY-AAAA-00 (00 = status for REACHED)
 * XXXX for the position along Y Axis in mm
 * YYYY for the position along Y Axis in mm
 * AAAA for the position in 1/10 deg
 * @param outputStream the outputStream to notify the main Board
 */
void notifyReached(OutputStream* outputStream);

/**
 * Notify the main Board that the motorBoard has failed to reach the asked position
 * It sends a message like this
 * kXXXX-YYYY-AAAA-01 (01 = status for FAILED)
 * XXXX for the position along Y Axis in mm
 * YYYY for the position along Y Axis in mm
 * AAAA for the position in 1/10 deg
 * @param outputStream the outputStream to notify the main Board
 */
void notifyFailed(OutputStream* outputStream);

/**
 * Notify the main Board that the motorBoard is moving.
 * It sends a message like this
 * kXXXX-YYYY-AAAA-02 (01 = status for MOVING)
 * XXXX for the position along Y Axis in mm
 * YYYY for the position along Y Axis in mm
 * AAAA for the position in 1/10 deg
 * @param outputStream the outputStream to notify the main Board
 */
void notifyMoving(OutputStream* outputStream);

// TODO
void notifyObstacle(OutputStream* outputStream);

#endif

