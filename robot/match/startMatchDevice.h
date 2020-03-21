#ifndef START_MATCH_DEVICE_H
#define START_MATCH_DEVICE_H

/**
 * Small unit of code which detects the start of the match, by looping the
 * state of a pin
 */

#include <stdbool.h>

#include "startMatch.h"

#include "../../common/eeprom/eeprom.h"
#include "../../common/io/outputStream.h"

#include "../../device/device.h"

#include "../../robot/robot.h"
#include "../../robot/config/robotConfig.h"

/**
 * Returns the deviceDescriptor of the end Match Detector.
 * @param startMatch the startMatch structure with all information needed.
 * @return a device descriptor on startMatch Device
 */
DeviceDescriptor* getStartMatchDeviceDescriptor(StartMatch* startMatch);

/**
 * Show the message to indicate that we wait for the match.
 * @param pcOutputStream the stream to the pc motherboard
 */
void notifyWaitingStart(StartMatch* startMatch, OutputStream* pcOutputStream);

/**
 * Inform user that the match is started.
 * @param the stream to the pc motherboard
 */
void notifyStarted(StartMatch* startMatch, OutputStream* pcOutputStream);

#endif
