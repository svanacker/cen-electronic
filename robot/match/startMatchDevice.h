#ifndef START_MATCH_DEVICE_H
#define START_MATCH_DEVICE_H

/**
 * Small unit of code which detects the start of the match, by looping the
 * state of a pin
 */

#include <stdbool.h>

#include "startMatchDetector.h"

#include "../../device/device.h"

#include "../../common/eeprom/eeprom.h"
#include "../../common/io/outputStream.h"


/**
* Define a call back function which must be called during loopUntilStart.
*/
typedef unsigned char handleFunctionType(void);

/**
* Returns the deviceDescriptor of the end Match Detector.
* @param startMatchDetector the startMatchDetector structure to be independant of the hardware.
* @return a device descriptor on startMatchDetector Device
*/
DeviceDescriptor* getStartMatchDeviceDescriptor(StartMatchDetector* startMatchDetector, Eeprom* eeprom);

/**
* Init the device.
*/
void initStartMatchDetector();

/**
* Indicates if the match is started or not.
*/
unsigned int isStartMatchDetectorOk();

/**
* Wait before start, but call the function given in argument.
*/
void loopUntilStart();

/**
* Test if the match is started or not.
* @return true if the match is started, false else.
*/
bool isStarted(void);

/**
* Show the message to indicate that we wait for the match.
* @param pcOutputStream the stream to the pc motherboard
*/
void notifyWaitingStart(OutputStream* pcOutputStream);

/**
* Inform user that the match is started.
* @param the stream to the pc motherboard
*/
void notifyStarted(OutputStream* pcOutputStream);

#endif
